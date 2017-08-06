//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAMVISITOR_H
#define STIL_INTERPRETER_STILPROGRAMVISITOR_H


#include "STILProgram.h"
#include "../STILCustomVisitor.h"

using namespace std;
using namespace antlr4;
using namespace parser;

class STILProgramVisitor : public STILCustomVisitor {

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

    virtual antlrcpp::Any visitTiming(STILParser::TimingContext* ctx) override;

    virtual antlrcpp::Any visitWaveform_table(STILParser::Waveform_tableContext* ctx) override;

    virtual antlrcpp::Any visitWaveforms(STILParser::WaveformsContext* ctx) override;

    virtual antlrcpp::Any visitWaveform(STILParser::WaveformContext* ctx) override;

    virtual antlrcpp::Any visitEvent(STILParser::EventContext* ctx) override;
};


#endif //STIL_INTERPRETER_STILPROGRAMVISITOR_H
