//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILINTERPRETER_H
#define STIL_INTERPRETER_STILINTERPRETER_H

#include <STILLexer.h>
#include <STILParser.h>
#include "program/STILProgram.h"
#include "STILCustomVisitor.h"

using namespace std;
using namespace antlr4;
using namespace parser;

class STILInterpreter : public STILCustomVisitor {

private:
    STILProgram program;

    ifstream stil_input;
    ofstream pattern_stream;
    ofstream timing_stream;

public:
    STILInterpreter(string stil_file, string pattern_file, string timing_file);

    void run();

    void run(string pattern_exec);

    virtual antlrcpp::Any visitPattern_exec(STILParser::Pattern_execContext* context) override;

};


#endif //STIL_INTERPRETER_STILINTERPRETER_H
