//
// Created by Gonzalo Solera on 04/08/2017.
//

#include "SignalGroup.h"

SignalGroup::SignalGroup(string id, vector<string>& signals, WFCMaps& wfcmaps) : Identifiable(id) {
    this->signals = signals;
    this->wfcmaps = wfcmaps;
}

SignalGroup::SignalGroup(const Signal &signal) : Identifiable(signal.id) {
    this->signals = vector<string>(1, signal.id);
}
