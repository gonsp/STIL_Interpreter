//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_PATTERNEXEC_H
#define STIL_INTERPRETER_PATTERNEXEC_H


#include <tree/ParseTree.h>
#include <STILParser.h>

using namespace parser;

class PatternExec {

public:

    STILParser::Pattern_execContext* ast;

    PatternExec();
    PatternExec(STILParser::Pattern_execContext* ast);

};


#endif //STIL_INTERPRETER_PATTERNEXEC_H
