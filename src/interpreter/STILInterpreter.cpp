//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <ANTLRInputStream.h>
#include <STILLexer.h>
#include <STILParser.h>
#include "STILInterpreter.h"
#include "program/STILProgramVisitor.h"

using namespace std;
using namespace antlr4;
using namespace parser;

STILInterpreter::STILInterpreter(istream& stream) {
    ANTLRInputStream input(stream);
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    cout << "Starting file parsing" << endl;
    STILParser parser(&tokens);
    ast = parser.program();
    cout << "File parsed succesfully" << endl;

    cout << "Generating internal representation of the program" << endl;
    STILProgramVisitor programVisitor(&program);
    programVisitor.visit(ast);
    cout << "Generation successful" << endl;
}

void STILInterpreter::run(ostream &vector_stream, ostream &timing_stream) {
    cout << "Executing" << endl;

    visit(ast);
}