//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "SignalState.h"

using namespace std;

SignalState::SignalState(STILProgram* program) {
    this->program = program;
    next_vector = program->signals;
}

void SignalState::execute_assigs(list<Assig> assigs) {
    Signals assig_result;
    for(auto it = assigs.begin(); it != assigs.end(); ++it) {
        cout << it->first << " = " << it->second << endl;
        SignalGroup& signalGroup = program->signalGroups[it->first];
        vector<string>& signals = signalGroup.signals;
        for(int i = 0; i < signals.size(); ++i) {
            if(assig_result.find(signals[i]) == assig_result.end()) {
                assig_result[signals[i]].value = it->second[i];
            } else {
                char wfc1 = assig_result[signals[i]].value;
                char wfc2 = it->second[i];
                string from = {wfc1, wfc2};
                assig_result[signals[i]].value = signalGroup.wfcmaps[from];
            }
        }
    }
    for(auto it = assig_result.begin(); it != assig_result.end(); ++it) {
        next_vector[it->first].value = it->second.value;
    }
}

void SignalState::clock_cycle(ostream& output) {
    output << " > " << "t" << waveform_table.id_no_quotes() << " ";
    for(auto it_signal = next_vector.begin(); it_signal != next_vector.end(); ++it_signal) {

        char wfc = it_signal->second.value;
        assert(wfc != '#' && wfc != '%'); // Check that it has been substituted by a parameter

        WaveForms& waveForms = program->waveFormTables[waveform_table.id].waveforms;

        bool found = false;
        WaveForm::WaveFormEvent event;
        for(int i = 0; i < waveForms.size(); ++i) {
            if(program->signalGroups[waveForms[i].id].contains(it_signal->second.id)) {
                if(wfc == waveForms[i].wfc) {
                    found = true;
                    event = waveForms[i].events[0];
                    break;
                }
            }
        }
        assert(found);
        output << event.event << " ";
    }
    output << ";" << endl;
}
