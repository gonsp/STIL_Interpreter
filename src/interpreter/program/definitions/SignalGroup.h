//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNALGROUP_H
#define STIL_INTERPRETER_SIGNALGROUP_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Identifiable.h"
#include "Signal.h"

using namespace std;

class SignalGroup : public Identifiable {

public:

    typedef unordered_map<string, char> WFCMaps;

    vector<string> signals;
    WFCMaps wfcmaps;

    SignalGroup() : Identifiable() {}

    SignalGroup(string id, vector<string>& signals, WFCMaps& wfcMaps);

    SignalGroup(const Signal& signal);

};


#endif //STIL_INTERPRETER_SIGNALGROUP_H
