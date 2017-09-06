//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILINTERPRETER_H
#define STIL_INTERPRETER_STILINTERPRETER_H

#include <stack>
#include <STILLexer.h>
#include <STILParser.h>
#include <fstream>
#include "stil/STILProgram.h"
#include "STILCustomVisitor.h"
#include "STILState.h"
#include "teradyne/STILConfig.h"
#include "teradyne/STILPatternGenerator.h"
#include "teradyne/STILTimingGenerator.h"

using namespace std;
using namespace antlr4;
using namespace parser;

class STILInterpreter : public STILCustomVisitor {

private:
    STILProgram program;

    string stil_file;
    string pattern_file;
    string timing_file;

    ifstream stil_input;

    ContextStack contextStack;
    STILState signalState;
    STILPatternGenerator patternGenerator;
    STILTimingGenerator timingGenerator;

    int actual_line;

    virtual antlrcpp::Any visitPattern_exec(STILParser::Pattern_execContext* ctx) override;

    virtual antlrcpp::Any visitPattern_burst_call(STILParser::Pattern_burst_callContext* ctx) override;

    virtual antlrcpp::Any visitPattern_list(STILParser::Pattern_listContext* ctx) override;

    virtual antlrcpp::Any visitInst(STILParser::InstContext* ctx) override;

    virtual antlrcpp::Any visitLoop(STILParser::LoopContext* ctx) override;

    virtual antlrcpp::Any visitShift(STILParser::ShiftContext* ctx) override;

    virtual antlrcpp::Any visitW_inst(STILParser::W_instContext* ctx) override;

    virtual antlrcpp::Any visitV_inst(STILParser::V_instContext* ctx) override;

    virtual antlrcpp::Any visitC_inst(STILParser::C_instContext* ctx) override;

    virtual antlrcpp::Any visitF_inst(STILParser::F_instContext* ctx) override;

    virtual antlrcpp::Any visitCall_inst(STILParser::Call_instContext* ctx) override;

    virtual antlrcpp::Any visitMacro_inst(STILParser::Macro_instContext* ctx) override;

    virtual antlrcpp::Any visitStop_inst(STILParser::Stop_instContext* ctx) override;

    virtual antlrcpp::Any visitIddq_inst(STILParser::Iddq_instContext* ctx) override;

//    virtual antlrcpp::Any visitAssig(STILParser::AssigContext* ctx) override;

public:
    STILInterpreter(string stil_file, string pattern_file, string timing_file, STILConfig& config);

    void run();

    void run(string pattern_exec);
};


#endif //STIL_INTERPRETER_STILINTERPRETER_H
