//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_WAVEFORMTABLE_H
#define STIL_INTERPRETER_WAVEFORMTABLE_H

#include <unordered_map>
#include "Identifiable.h"
#include "WaveForm.h"
#include "SignalGroup.h"

typedef unordered_map<string, SignalGroup> SignalGroups;
typedef vector<WaveForm> WaveForms;

class WaveFormTable : public Identifiable {

public:

    float period;
    WaveForms waveforms;

    WaveFormTable() : Identifiable() {}

    WaveFormTable(string id, float period, WaveForms& waveforms);

    string get_event_seq(string signal_id, char wfc, SignalGroups& signalGroups);

};


#endif //STIL_INTERPRETER_WAVEFORMTABLE_H
