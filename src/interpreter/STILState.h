//
// Created by Gonzalo Solera on 08/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNALSTATE_H
#define STIL_INTERPRETER_SIGNALSTATE_H

#include <string>
#include <vector>
#include "stil/definitions/STILProgram.h"

using namespace std;

class STILState {

private:
    STILProgram* program;

public:
    typedef pair<string, string> Assig;

    Signals next_vector;
    Identifiable active_table;

    int max_param_size = 0;
    int* stil_line;

    STILState() {}

    STILState(STILProgram* program, int* stil_line);

    void set_params(list<Assig> params);

    void clear_params();

    void restore_params(STILState& prev_state);

    void execute_assigs(list<Assig> assigs);

    void set_padding_to_params(int max_size);
};


#endif //STIL_INTERPRETER_SIGNALSTATE_H
