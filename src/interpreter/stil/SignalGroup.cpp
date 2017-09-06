//
// Created by Gonzalo Solera on 04/08/2017.
//

#include "SignalGroup.h"

SignalGroup::SignalGroup(string id, vector<string>& signals, WFCMaps& wfcmaps) : Identifiable(id) {
    this->signals = signals;
    this->wfcmaps = wfcmaps;
}

SignalGroup::SignalGroup(const Signal &signal) : Identifiable(signal) {
    this->signals = vector<string>(1, signal);
}

bool SignalGroup::contains(string signal_id) {
    for(int i = 0; i < signals.size(); ++i) {
        if(signals[i] == signal_id) {
            return true;
        }
    }
    return false;
}
