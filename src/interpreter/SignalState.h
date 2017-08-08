//
// Created by Gonzalo Solera on 08/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNALSTATE_H
#define STIL_INTERPRETER_SIGNALSTATE_H

#include <string>
#include <vector>
#include "program/STILProgram.h"

using namespace std;

class SignalState {

private:

    STILProgram* program;

public:
    vector<char> next_vector;
    string waveform_table;

    SignalState() {}

    SignalState(STILProgram* program);

    void clock_cicle(ostream& output);
};


#endif //STIL_INTERPRETER_SIGNALSTATE_H
