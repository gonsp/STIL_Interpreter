//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <ANTLRInputStream.h>
#include <STILLexer.h>
#include <STILParser.h>
#include "STILInterpreter.h"
#include "program/STILProgramVisitor.h"


STILInterpreter::STILInterpreter(istream& stream) {
    ANTLRInputStream input(stream);
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    cout << "Starting file parsing" << endl;
    parser = new STILParser(&tokens);
    ParseTree* ast = parser->program();
    cout << "File parsed successfully" << endl;

    cout << "Generating internal representation of the program" << endl;
    STILProgramVisitor programVisitor(&program);
    programVisitor.visit(ast);
    cout << "Generation successful" << endl;
}

STILInterpreter::~STILInterpreter() {
    delete parser;
}

void STILInterpreter::run(ostream &vector_stream, ostream &timing_stream) {
    cout << "Starting interpretation" << endl;
    visit(program.get_main());
    cout << "Done" << endl;
}

antlrcpp::Any STILInterpreter::visitProgram(STILParser::ProgramContext* ctx) {
    return 0;
}