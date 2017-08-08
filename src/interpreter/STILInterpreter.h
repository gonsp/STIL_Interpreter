//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILINTERPRETER_H
#define STIL_INTERPRETER_STILINTERPRETER_H

#include <stack>
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

    vector<char> next_vector;
    string waveform_table;

    ContextStack contextStack;

public:
    STILInterpreter(string stil_file, string pattern_file, string timing_file);

    void run();

    void run(string pattern_exec);

    virtual antlrcpp::Any visitPattern_exec(STILParser::Pattern_execContext* ctx) override;

    virtual antlrcpp::Any visitPattern_burst_call(STILParser::Pattern_burst_callContext* ctx) override;

    virtual antlrcpp::Any visitPattern_list(STILParser::Pattern_listContext* ctx) override;

    virtual antlrcpp::Any visitLoop(STILParser::LoopContext* ctx) override;

    virtual antlrcpp::Any visitShift(STILParser::ShiftContext* ctx) override;

    virtual antlrcpp::Any visitW_inst(STILParser::W_instContext* ctx) override;

    virtual antlrcpp::Any visitCall_inst(STILParser::Call_instContext* ctx) override;

    virtual antlrcpp::Any visitMacro_inst(STILParser::Macro_instContext* ctx) override;

    virtual antlrcpp::Any visitStop_inst(STILParser::Stop_instContext* ctx) override;

};


#endif //STIL_INTERPRETER_STILINTERPRETER_H
