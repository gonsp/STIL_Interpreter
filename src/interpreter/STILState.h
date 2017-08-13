//
// Created by Gonzalo Solera on 08/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNALSTATE_H
#define STIL_INTERPRETER_SIGNALSTATE_H

#include <string>
#include <vector>
#include "program/STILProgram.h"

using namespace std;

class STILState {

private:

    STILProgram* program;


public:

    typedef pair<string, string> Assig;

    Signals next_vector;
    Identifiable waveform_table;

    STILState() {}

    STILState(STILProgram* program);

    void set_params(list<Assig> params);

    void clear_params();

    void restore_params(const STILState& prev_state);

    void execute_assigs(list<Assig> assigs);

    void clock_cycle(ostream& output);
};


#endif //STIL_INTERPRETER_SIGNALSTATE_H
