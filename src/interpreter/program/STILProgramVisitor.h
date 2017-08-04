//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAMVISITOR_H
#define STIL_INTERPRETER_STILPROGRAMVISITOR_H


#include <STILBaseVisitor.h>
#include "STILProgram.h"

using namespace std;
using namespace antlr4;
using namespace parser;

class STILProgramVisitor : public STILBaseVisitor {

private:
    STILProgram& program;

public:

    STILProgramVisitor(STILProgram& program) : program(program) {}

    virtual antlrcpp::Any visitProgram(STILParser::ProgramContext* ctx) override;

    virtual antlrcpp::Any visitSignals(STILParser::SignalsContext* ctx) override;

    virtual antlrcpp::Any visitSignal(STILParser::SignalContext* ctx) override;

    virtual antlrcpp::Any visitSignal_dir(STILParser::Signal_dirContext* ctx) override;

    virtual antlrcpp::Any visitSignal_groups(STILParser::Signal_groupsContext* ctx) override;

    virtual antlrcpp::Any visitSignal_group(STILParser::Signal_groupContext* ctx) override;

    virtual antlrcpp::Any visitSignal_list(STILParser::Signal_listContext* ctx) override;

    virtual antlrcpp::Any visitTerminal(tree::TerminalNode* node) override {
        return node->getText();
    }
};


#endif //STIL_INTERPRETER_STILPROGRAMVISITOR_H
