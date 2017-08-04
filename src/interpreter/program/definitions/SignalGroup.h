//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNALGROUP_H
#define STIL_INTERPRETER_SIGNALGROUP_H

#include <string>
#include <vector>
#include "Identifiable.h"

using namespace std;

class SignalGroup : public Identifiable {

public:

    vector<string> signals;

    SignalGroup() : Identifiable() {}

    SignalGroup(string id, vector<string> signals);

};


#endif //STIL_INTERPRETER_SIGNALGROUP_H
