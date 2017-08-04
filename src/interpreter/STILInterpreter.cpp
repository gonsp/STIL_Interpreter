//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <ANTLRInputStream.h>
#include <STILLexer.h>
#include <STILParser.h>
#include "STILInterpreter.h"
#include "program/STILProgramVisitor.h"
#include "program/STILProgram.h"

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
    STILProgramVisitor programVisitor(program);
    programVisitor.visit(ast);
    cout << "Generation successful" << endl;
}

STILInterpreter::~STILInterpreter() {
    delete parser;
}

void STILInterpreter::run(ofstream& vector_stream, ofstream& timing_stream) {
    cout << "Running default pattern_exec block" << endl;
    visit(program.patternExecs[GLOBAL_DEF].ast);
    cout << "Done" << endl;
}

void STILInterpreter::run(ofstream& vector_stream, ofstream& timing_stream, const string& pattern_exec) {
    cout << "Starting interpretation" << endl;
    visit(program.patternExecs[pattern_exec].ast);
    cout << "Done" << endl;
}

antlrcpp::Any STILInterpreter::visitProgram(STILParser::ProgramContext* ctx) {
    return 0;
}