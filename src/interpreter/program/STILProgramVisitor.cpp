//
// Created by Gonzalo Solera on 03/08/2017.
//

#include "STILProgramVisitor.h"

antlrcpp::Any STILProgramVisitor::visitProgram(STILParser::ProgramContext* ctx) {
    visit(ctx->signals());
    visit(ctx->signal_groups());

    return NULL;
}

antlrcpp::Any STILProgramVisitor::visitSignals(STILParser::SignalsContext* ctx) {
    for(int i = 0; i < ctx->signal().size(); ++i) {
        visit(ctx->signal(i));
    }
    return NULL;
}

antlrcpp::Any STILProgramVisitor::visitSignal(STILParser::SignalContext* ctx) {
    string id = visit(ctx->id());
    signal_dir dir = visit(ctx->signal_dir());
    program.signals[id] = Signal(id, dir);
    program.signalGroups[id] = SignalGroup(id, vector<string>(1, id));
    return NULL;
}

antlrcpp::Any STILProgramVisitor::visitSignal_dir(STILParser::Signal_dirContext* ctx) {
    if(ctx->getText() == "In") {
        return IN;
    } else if(ctx->getText() == "Out") {
        return OUT;
    } else {
        return INOUT;
    }
}

antlrcpp::Any STILProgramVisitor::visitSignal_groups(STILParser::Signal_groupsContext* ctx) {
    for(int i = 0; i < ctx->signal_group().size(); ++i) {
        visit(ctx->signal_group(i));
    }
    return NULL;
}

antlrcpp::Any STILProgramVisitor::visitSignal_group(STILParser::Signal_groupContext* ctx) {
    string id = visit(ctx->id());
    vector<string> signals = visit(ctx->signal_list());
    program.signalGroups[id] = SignalGroup(id, signals);
    return NULL;
}

antlrcpp::Any STILProgramVisitor::visitSignal_list(STILParser::Signal_listContext* ctx) {
    vector<string> signal_list;
    for(int i = 0; i < ctx->id().size(); ++i) {
        string id = visit(ctx->id(i));
        signal_list.push_back(id);
    }
    return signal_list;
}




