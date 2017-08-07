//
// Created by Gonzalo Solera on 03/08/2017.
//

#include "STILProgramVisitor.h"
#include "definitions/WaveFormTable.h"

antlrcpp::Any STILProgramVisitor::visitProgram(STILParser::ProgramContext* ctx) {
    visit(ctx->signals());
    visit(ctx->signal_groups());
    visit(ctx->timing_l());
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
    program.signalGroups[id] = SignalGroup(program.signals[id]); // Adding a default signalgroup
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
    SignalGroup::WFCMaps wfcmaps;
    if(ctx->signal_attributes() != NULL && ctx->signal_attributes()->wfc_map() != NULL) {
        SignalGroup::WFCMaps aux = visit(ctx->signal_attributes()->wfc_map());
        wfcmaps = aux;
    }
    program.signalGroups[id] = SignalGroup(id, signals, wfcmaps);
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

antlrcpp::Any STILProgramVisitor::visitWfc_map(STILParser::Wfc_mapContext* ctx) {
    SignalGroup::WFCMaps wfcmaps;
    for(int i = 0; i < ctx->map_rule().size(); ++i) {
        MapRule map_rule = visit(ctx->map_rule(i));
        wfcmaps[map_rule.first] = map_rule.second;
    }
    return wfcmaps;
}

antlrcpp::Any STILProgramVisitor::visitMap_rule(STILParser::Map_ruleContext* ctx) {
    string from = visit(ctx->wfc(0));
    string to = visit(ctx->wfc(1));
    return MapRule(from, to[0]);
}

antlrcpp::Any STILProgramVisitor::visitTiming(STILParser::TimingContext* ctx) {
    string id = GLOBAL_DEF;
    if(ctx->id() != NULL) {
        string aux = visit(ctx->id()); // This needs declaration & definition at the same time
        id = aux;
    }
    program.timings[id] = Timing(id);
    for(int i = 0; i < ctx->waveform_table().size(); ++i) {
        WaveFormTable table = visit(ctx->waveform_table(i));
        program.timings[id].waveFormTables[table.id] = table;
    }
    return NULL;
}

antlrcpp::Any STILProgramVisitor::visitWaveform_table(STILParser::Waveform_tableContext* ctx) {
    string id = visit(ctx->id());
    float period = visit(ctx->period());
    WaveForms waveforms = visit(ctx->waveforms());
    WaveFormTable table(id, period, waveforms);
    return table;
}

antlrcpp::Any STILProgramVisitor::visitWaveforms(STILParser::WaveformsContext* ctx) {
    WaveForms waveforms;
    for(int i = 0; i < ctx->waveform().size(); ++i) {
        WaveForm waveform = visit(ctx->waveform(i));
        waveforms[waveform.id] = waveform;
    }
    return waveforms;
}

antlrcpp::Any STILProgramVisitor::visitWaveform(STILParser::WaveformContext* ctx) {
    string id = visit(ctx->id());
    string wfc = visit(ctx->wfc());
    vector<WaveForm::WaveFormEvent> events;
    for(int i = 0; i < ctx->event().size(); ++i) {
        WaveForm::WaveFormEvent event = visit(ctx->event(i));
        events.push_back(event);
    }
    return WaveForm(id, wfc[0], events);
}

antlrcpp::Any STILProgramVisitor::visitEvent(STILParser::EventContext* ctx) {
    float time = visit(ctx->time_expr());
    WaveForm::WaveFormEvent::Event event = visit(ctx->event_code());
    return WaveForm::WaveFormEvent(time, event);
}

antlrcpp::Any STILProgramVisitor::visitEvent_code(STILParser::Event_codeContext* ctx) {
    string event_code = visit(ctx->CHARS());
    switch(event_code[0]) {
        case 'D': return WaveForm::WaveFormEvent::ForceDown;
        case 'U': return WaveForm::WaveFormEvent::ForceUp;
        case 'Z': return WaveForm::WaveFormEvent::ForceOff;
        case 'L': return WaveForm::WaveFormEvent::CompareLow;
        case 'H': return WaveForm::WaveFormEvent::CompareHigh;
        case 'X': return WaveForm::WaveFormEvent::CompareUnknown;
        case 'T': return WaveForm::WaveFormEvent::CompareOff;
        case 'N': return WaveForm::WaveFormEvent::ForceUnknown;
        default: cerr << "Unrecognized event: " << event_code[0] << endl; exit(1);
    }
}