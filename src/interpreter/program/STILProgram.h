//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAM_H
#define STIL_INTERPRETER_STILPROGRAM_H

#include <string>
#include <map>
#include <tree/ParseTree.h>
#include "Signal.h"

using namespace std;
using namespace antlr4;
using namespace tree;

class STILProgram {

    typedef map<string, Signal> Signals;

public:
    Signals signals;

    STILProgram();

    ParseTree* get_main();
};


#endif //STIL_INTERPRETER_STILPROGRAM_H
