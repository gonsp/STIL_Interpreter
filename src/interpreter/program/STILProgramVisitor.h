//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAMVISITOR_H
#define STIL_INTERPRETER_STILPROGRAMVISITOR_H


#include <STILBaseVisitor.h>
#include "STILProgram.h"

using namespace parser;
using namespace antlr4;

class STILProgramVisitor : public STILBaseVisitor {

private:
    STILProgram* program;

public:

    STILProgramVisitor(STILProgram* program) {
        this->program = program;
    }

    virtual antlrcpp::Any visitProgram(STILParser::ProgramContext* ctx) override {
        visitChildren(ctx);
        return program;
    }

    virtual antlrcpp::Any visitTerminal(tree::TerminalNode* node) override {
        return "token";
    }
};


#endif //STIL_INTERPRETER_STILPROGRAMVISITOR_H
