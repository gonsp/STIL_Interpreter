//
// Created by Gonzalo Solera on 04/08/2017.
//

#include "PatternExec.h"


PatternExec::PatternExec() {
    this->ast = NULL;
}

PatternExec::PatternExec(STILParser::Pattern_execContext *ast) {
    this->ast = ast;
}