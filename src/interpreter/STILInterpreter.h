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
    STILParser* parser; //This is needed because ast will be deleted when parser is pulled out of the stack
    STILProgram program;

public:
    STILInterpreter(istream& stream);
    ~STILInterpreter();

    void run(ofstream& vector_stream, ofstream& timing_stream);
    void run(ofstream& vector_stream, ofstream& timing_stream, const string& pattern_exec);

    virtual antlrcpp::Any visitProgram(STILParser::ProgramContext* ctx) override;

};


#endif //STIL_INTERPRETER_STILINTERPRETER_H
