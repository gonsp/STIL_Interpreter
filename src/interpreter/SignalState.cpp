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
    output << " > " << waveform_table << " ";
    for(auto it_signal = next_vector.begin(); it_signal != next_vector.end(); ++it_signal) {
        char wfc = it_signal->second.value;

        WaveForms& waveForms = program->waveFormTables[waveform_table].waveforms;

        WaveForm::WaveFormEvent event;

        for(auto it_waveform = waveForms.begin(); it_waveform != waveForms.end(); ++it_waveform) {
            if(program->signalGroups[it_waveform->second.id].contains(it_signal->second.id)) {
                if(wfc == it_waveform->second.wfc) {
                    event = it_waveform->second.events[0];
                    break;
                }
            }
        }
        output << event.event << " ";
    }
    output << ";" << endl;
}
