//
// Created by Gonzalo Solera on 03/08/2017.
//

#include "STILProgramVisitor.h"

STILProgramVisitor::STILProgramVisitor(STILProgram& program) : program(program) {
}

antlrcpp::Any STILProgramVisitor::visitProgram(STILParser::ProgramContext* ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any STILProgramVisitor::visitTerminal(tree::TerminalNode* node) {
    return "token";
}
