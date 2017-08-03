//
// Created by Gonzalo Solera on 03/08/2017.
//

#include "STILProgramVisitor.h"

STILProgramVisitor::STILProgramVisitor(STILProgram *program) {
    this->program = program;
}

antlrcpp::Any STILProgramVisitor::visitProgram(STILParser::ProgramContext *ctx) {
    visitChildren(ctx);
    return program;
}

antlrcpp::Any STILProgramVisitor::visitTerminal(tree::TerminalNode *node) {
    return "token";
}
