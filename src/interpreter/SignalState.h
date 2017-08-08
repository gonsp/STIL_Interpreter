//
// Created by Gonzalo Solera on 08/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNALSTATE_H
#define STIL_INTERPRETER_SIGNALSTATE_H

#include <string>
#include <vector>

using namespace std;

class SignalState {

public:
    vector<char> next_vector;
    string waveform_table;

    SignalState() {}

    SignalState(int size);

};


#endif //STIL_INTERPRETER_SIGNALSTATE_H
