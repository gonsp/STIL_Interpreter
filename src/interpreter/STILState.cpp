//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "STILState.h"

using namespace std;

STILState::STILState(STILProgram* program) {
    this->program = program;
    next_vector = program->signals;
}

void STILState::execute_assigs(list<Assig> assigs) {
    Signals assig_result;
    for(auto it = assigs.begin(); it != assigs.end(); ++it) {

        SignalGroup& signalGroup = program->signalGroups[it->first];
        vector<string>& signals = signalGroup.signals;

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
                    assert(signalGroup.wfcmaps[from] != ' ' && "WFC map not defined for this char join!");
                    assig_result[signals[i]].value = signalGroup.wfcmaps[from];
                }
            }
        }
    }
    for(auto it = assig_result.begin(); it != assig_result.end(); ++it) {
        next_vector[it->first].value = it->second.value;
    }
}

void STILState::clock_cycle(ostream& output) {
    output << "> " << "t" << waveform_table.format(program->config) << "   ";
    for(auto it_signal = next_vector.begin(); it_signal != next_vector.end(); ++it_signal) {

        // This is in case that a signal has been removed in the config file.
        // If it's removed, we don't print its value
        if(it_signal->second.format(program->config) == "") {
            continue;
        }

        char wfc = it_signal->second.value;
        assert(wfc != '?' && "WFC not defined for signal before clock_cycle!");
        assert(wfc != '#' && wfc != '%'); // Check that it has been substituted by a parameter

        if(wfc == '$') {
            wfc = program->config.scan_padding_in;
        } else if(wfc == '@') {
            wfc = program->config.scan_padding_out;
        }

        WaveForms& waveForms = program->waveFormTables[waveform_table.id].waveforms;

        bool found = false;
        int waveform = 0;
        while(waveform < waveForms.size() && !found) {
            if(program->signalGroups[waveForms[waveform].id].contains(it_signal->second.id)) {
                if(wfc == waveForms[waveform].wfc) {
                    found = true;
                    break;
                }
            }
            ++waveform;
        }
        assert(found);
        string event_seq = waveForms[waveform].event_seq();
        char tester_event = program->config.eventsMap[event_seq];
        if(tester_event == '\0') {
            cerr << "Event sequence \"" << event_seq << "\" for waveform " << waveForms[waveform].id << " in WaveFormTable: " << waveform_table.id << " not defined in config file" << endl;
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
            signal.params[signalGroup.id] = it->second;
            max_param_size = max(max_param_size, (int) it->second.size());
        } else {
            for(int s = 0; s < signalGroup.signals.size(); ++s) {
                Signal& signal = next_vector[signalGroup.signals[s]];
                signal.params[signalGroup.id] = {it->second[s]};
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

