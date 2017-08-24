//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "STILState.h"

using namespace std;

STILState::STILState(STILProgram* program, int* stil_line) {
    this->program = program;
    next_vector = program->signals;
    this->stil_line = stil_line;
}

void STILState::execute_assigs(list<Assig> assigs) {
    Signals assig_result;
    for(auto it = assigs.begin(); it != assigs.end(); ++it) {

        SignalGroup& signalGroup = program->signalGroups[it->first];
        vector<string>& signals = signalGroup.signals;

        assert(it->second.size() == signals.size());

        for(int i = 0; i < signals.size(); ++i) {

            char wfc = it->second[i];
            if(wfc == '#' || wfc == '%') {
                wfc = next_vector[signals[i]].solve_param_ref(it->first, wfc);
            }

            if(assig_result.find(signals[i]) == assig_result.end()) {
                assig_result[signals[i]].value = wfc;
            } else {
                char wfc1 = assig_result[signals[i]].value;
                char wfc2 = wfc;
                if(wfc1 != wfc2) {
                    string from = {wfc1, wfc2};
                    if(signalGroup.wfcmaps[from] == 0) {
                        cerr << "Error at line: " << *stil_line << endl;
                        cerr << "WFC map not defined for the char join of: " << from << " at signal: " << signals[i] << endl;
                        cerr << "In one instruction (V/C/F) you can only assign the same value "
                             << "to each signal in each assignation, or assign 2 different values "
                             << "but having a WFCMap defined for that SignalGroup and that combination of wfc" << endl;
                        exit(1);
                    };
                    assig_result[signals[i]].value = signalGroup.wfcmaps[from];
                }
            }
        }
    }
    for(auto it = assig_result.begin(); it != assig_result.end(); ++it) {
        next_vector[it->first].value = it->second.value;
        next_vector[it->first].refresh_params();
    }
}

void STILState::clock_cycle(ostream& output) {
    output << "> " << "t" << active_table.format(program->config) << "   ";
    for(auto it = next_vector.begin(); it != next_vector.end(); ++it) {

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

        WaveFormTable& table = program->waveFormTables[active_table.id];
        string event_seq = table.get_event_seq(it->second.id, wfc, program->signalGroups);

        char tester_event = program->config.eventsMap[event_seq];
        if(tester_event == '\0') {
            cerr << "Error at line: " << *stil_line << endl;
//            cerr << "Event sequence \"" << event_seq << "\" for waveform " << waveForms[waveform].id << " in WaveFormTable: " << active_table.id << " not defined in config file" << endl;
            cerr << "Please, define a correct config file that maps all the used permutations of STIL events inside the used waveforms to generate tester events" << endl;
            exit(1);
        }
        output << tester_event << " ";
    }
    output << ";" << endl;
}

void STILState::set_params(list<STILState::Assig> params) {
    for(auto it = params.begin(); it != params.end(); ++it) {
        SignalGroup& signalGroup = program->signalGroups[it->first];
        if(signalGroup.signals.size() == 1) {
            Signal& signal = next_vector[signalGroup.signals[0]];
            signal.params[signalGroup.id] = Signal::Param(it->first, it->second);
            max_param_size = max(max_param_size, (int) it->second.size());
        } else {
            for(int s = 0; s < signalGroup.signals.size(); ++s) {
                Signal& signal = next_vector[signalGroup.signals[s]];
                string aux = {it->second[s]};
                signal.params[signalGroup.id] = Signal::Param(it->first, aux);
            }
            max_param_size = max(max_param_size, 1);
        }
    }
}

void STILState::clear_params() {
    max_param_size = 0;
    for(auto it = next_vector.begin(); it != next_vector.end(); ++it) {
        it->second.params.clear();
    }
}

void STILState::restore_params(STILState& prev_state) {
    max_param_size = prev_state.max_param_size;
    for(auto it = next_vector.begin(); it != next_vector.end(); ++it) {
        it->second.params = prev_state.next_vector[it->second.id].params;
    }
}

void STILState::set_padding_to_params(int max_size) {
    for(auto it = next_vector.begin(); it != next_vector.end(); ++it) {
        it->second.set_padding_to_params(max_size);
    }
}

