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
    // TODO Replace this by the actual names of the generated timesets
    for(auto it = program->waveFormTables.begin(); it != program->waveFormTables.end(); ++it) {
        if(it != program->waveFormTables.begin()) {
            output << ",";
        }
        output << "t" << it->second.format(program->config);
    }
    output << ";" << endl;
    output << "vector($tset";
    vector<string signal_names = program->signals.formatted_names();
    for(int i = 0; i < signal_names.size(); ++i) {
        output << "," << signal_names[i];
    }
    output << ")" << endl;
    output << "{" << endl;
};

void STILPatternGenerator::clock_cycle(const STILState& state, STILTimingGenerator& timingGenerator) {
    output << string(padding, ' ');
    output << "> " << "t";
    long int offset = output.tellp();
    output << "                ";
//    output << "> " << "t" << state.active_table.format(program->config) << "   "; // This line was from before implementing the timing generation

    WaveFormTable& table = program->waveFormTables[state.active_table];
    TimeSet timeset(table.period);

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

        WaveForm& waveform = table.get_waveform(it->second, wfc, program->signalGroups);
        string event_seq = waveform.event_seq();

        STILConfig::EventsTranslation& translation = program->config.eventsMap[event_seq];
        char tester_event = translation.first;
        if(tester_event == '\0') {
            cerr << "Error at line: " << *stil_line << endl;
            cerr << "Event sequence \"" << event_seq << "\" in WaveFormTable: " << state.active_table << " not defined in config file" << endl;
            cerr << "Please, define a correct config file that maps all the used permutations of STIL events inside the used waveforms to generate tester events" << endl;
            exit(1);
        }
        output << tester_event << " ";

        WaveSet waveset(table.period, waveform, translation.second);
        timeset.add_waveset(waveset);
    }
    output << ";" << endl;

    padding = PADDING;
    prev_last_line_index = last_line_index;
    last_line_index = output.tellp();

    output.seekp(offset);
    output << timingGenerator.add_timeset(timeset);
    output.seekp(last_line_index);
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
