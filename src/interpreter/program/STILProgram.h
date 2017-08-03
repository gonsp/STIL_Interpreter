//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAM_H
#define STIL_INTERPRETER_STILPROGRAM_H

#include <string>
#include <map>
#include "Signal.h"

using namespace std;

class STILProgram {

    typedef map<string, Signal> Signals;

public:
    Signals signals;

    STILProgram();

};


#endif //STIL_INTERPRETER_STILPROGRAM_H
