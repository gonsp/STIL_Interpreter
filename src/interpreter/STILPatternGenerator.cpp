//
// Created by Gonzalo Solera on 04/09/2017.
//

#include "STILPatternGenerator.h"

STILPatternGenerator::STILPatternGenerator(string pattern_file, STILProgram* program, int* stil_line) {
    this->program = program;
    this->stil_line = stil_line;
    output.open(pattern_file);
}

void STILPatternGenerator::print_headers() {
    output << "opcode_mode=extended;" << endl;
    output << "import tset ";
    for(auto it = program->waveFormTables.begin(); it != program->waveFormTables.end(); ++it) {
        if(it != program->waveFormTables.begin()) {
            output << ",";
        }
        output << "t" << it->second.format(program->config);
    }
    output << ";" << endl;
    output << "vector($tset";
    for(auto it = program->signals.begin(); it != program->signals.end(); ++it) {
        string formated_id = it->second.format(program->config);
        if(formated_id != "") {
            output << "," << formated_id;
        }
    }
    output << ")" << endl;
    output << "{" << endl;
};

void STILPatternGenerator::clock_cycle(const STILState& state, STILTimingGenerator& timingGenerator) {
    output << string(padding, ' ');
    output << "> " << "t" << state.active_table.format(program->config) << "   ";

    for(auto it = state.next_vector.begin(); it != state.next_vector.end(); ++it) {

        // This is in case that a signal has been removed in the config file.
        // If it's removed, we don't print its value
        if(it->second.format(program->config) == "") {
            continue;
        }

        char wfc = it->second.value;
        assert(wfc != '?' && "WFC not defined for signal before clock_cycle!");
        assert(wfc != '#' && wfc != '%'); // Check that it has been substituted by a parameter

        if(wfc == '$') {
            wfc = program->config.scan_padding_in;
        } else if(wfc == '@') {
            wfc = program->config.scan_padding_out;
        }

        WaveFormTable& table = program->waveFormTables[state.active_table.id];
        string event_seq = table.get_event_seq(it->second.id, wfc, program->signalGroups);

        if(event_seq == "") {
            cerr << "Error at line: " << *stil_line << endl;
            cerr << "Waveform not found for signal: " << it->second.id << " and WFC: " << wfc << endl;
            exit(1);
        }

        char tester_event = program->config.eventsMap[event_seq];
        if(tester_event == '\0') {
            cerr << "Error at line: " << *stil_line << endl;
            cerr << "Event sequence \"" << event_seq << "\" in WaveFormTable: " << state.active_table.id
                 << " not defined in config file" << endl;
            cerr << "Please, define a correct config file that maps all the used permutations of STIL events inside the used waveforms to generate tester events"
                 << endl;
            exit(1);
        }
        output << tester_event << " ";
    }
    output << ";" << endl;

    padding = PADDING;
    prev_last_line_index = last_line_index;
    last_line_index = output.tellp();
}

void STILPatternGenerator::finish() {
    output << "}" << endl;
    output.seekp(prev_last_line_index);
    output << "halt";
    output.close();
}

void STILPatternGenerator::print_tester_inst(string instruction) {
    output << instruction;
    padding -= instruction.size();
}

void STILPatternGenerator::print_iddq() {
    output << program->config.iddq_action;
}
