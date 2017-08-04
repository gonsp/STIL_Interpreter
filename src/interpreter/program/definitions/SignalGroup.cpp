//
// Created by Gonzalo Solera on 04/08/2017.
//

#include "SignalGroup.h"

SignalGroup::SignalGroup(string id, vector<string> signals) : Identifiable(id) {
    this->signals = signals;
}
