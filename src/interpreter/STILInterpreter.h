//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILINTERPRETER_H
#define STIL_INTERPRETER_STILINTERPRETER_H

#include <STILBaseVisitor.h>
#include "program/STILProgram.h"

using namespace std;
using namespace antlr4;
using namespace parser;

class STILInterpreter : public STILBaseVisitor {

private:
    tree::ParseTree* ast;
    STILProgram program;

public:
    STILInterpreter(istream& stream);

    void run(ostream &vector_stream, ostream &timing_stream);
};


#endif //STIL_INTERPRETER_STILINTERPRETER_H
