//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <ANTLRInputStream.h>
#include "STILInterpreter.h"
#include "program/STILProgramVisitor.h"
#include "STILState.h"

STILInterpreter::STILInterpreter(string stil_file, string pattern_file, string timing_file, STILConfig& config) : program(config) {
    stil_input.open(stil_file);
    pattern_stream.open(pattern_file);
    timing_stream.open(timing_file);
}

void STILInterpreter::run() {
    cout << "Running default pattern_exec block" << endl;
    cout << "(You can specify the pattern_exec block with an additional argument)" << endl;
    run(GLOBAL_DEF);
}

void STILInterpreter::run(string pattern_exec) {
    ANTLRInputStream input(stil_input);
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    cout << "--------------------------------------" << endl;

    cout << "Starting file parsing" << endl;
    STILParser parser(&tokens);
    ParseTree* ast = parser.program();
    cout << "File parsed successfully" << endl;

    cout << "--------------------------------------" << endl;

    cout << "Generating internal representation of the program" << endl;
    STILProgramVisitor programVisitor(program);
    programVisitor.visit(ast);
    cout << "Generation successful" << endl;

    cout << "--------------------------------------" << endl;

    cout << "Starting interpretation" << endl;
    signalState = STILState(&program);
    visit(program.patternExecs[pattern_exec]);
    cout << "Done" << endl;
}

antlrcpp::Any STILInterpreter::visitPattern_exec(STILParser::Pattern_execContext* ctx) {
//    generate_headers();
    pattern_stream << "{" << endl;
    contextStack.push(PatternContext()); // Base context
    for(int i = 0; i < ctx->pattern_burst_call().size(); ++i) {
        visit(ctx->pattern_burst_call(i));
        assert(contextStack.size() == 1); // Needs to remain just the base context
    }
    pattern_stream << "}" << endl;
    insert_halt();
    pattern_stream.close();
    timing_stream.close();
    return NULL;
}

antlrcpp::Any STILInterpreter::visitPattern_burst_call(STILParser::Pattern_burst_callContext* ctx) {
    string id = visit(ctx->id());
    cout << "Executing pattern_burst: " << id << endl;
    cout << "Merging new context" << endl;
    contextStack.push(program.patternBursts[id].context);
    visit(program.patternBursts[id].ast);
    cout << "Executed pattern_burst: " << id << endl;
    contextStack.pop();
    return NULL;
}

antlrcpp::Any STILInterpreter::visitPattern_list(STILParser::Pattern_listContext* ctx) {
    for(int i = 0; i < ctx->pattern_call().size(); ++i) {
        string id = visit(ctx->pattern_call(i)->id());
        bool explicit_context = ctx->pattern_call(i)->context() != NULL;
        if(explicit_context) {
            PatternContext context = visit(ctx->pattern_call(i)->context());
            contextStack.push(context);
        }
        if(program.patternBursts.find(id) != program.patternBursts.end()) {
            cout << "Calling pattern_burst: " << id << endl;
            visit(program.patternBursts[id].ast);
        } else {
            cout << "Calling pattern: " << id << endl;
            visit(program.patterns[id]);
        }
        if(explicit_context) {
            contextStack.pop();
        }
    }
    return NULL;
}



antlrcpp::Any STILInterpreter::visitLoop(STILParser::LoopContext* ctx) {
    cout << "Executing loop" << endl;
    int times = visit(ctx->int_t());
    if(ctx->inst_list()->children.size() == 1) {
        string s = "repeat " + to_string(times);
        pattern_stream << s;
        padding -= s.size();
        visit(ctx->inst_list());
    } else {
        while(times > 0) {
            visit(ctx->inst_list());
            --times;
        }
    }
    return NULL;
}

antlrcpp::Any STILInterpreter::visitShift(STILParser::ShiftContext* ctx) {
    cout << "Executing shift" << endl;
    int times = signalState.max_param_size;
    signalState.set_padding_to_params(times);
    while(times > 0) {
        visit(ctx->inst_list());
        --times;
    }
    return NULL;
}

antlrcpp::Any STILInterpreter::visitW_inst(STILParser::W_instContext* ctx) {
    string id = visit(ctx->id());
    if(id != signalState.waveform_table.id) {
        cout << "Changing active waveform_table to: " << id << endl;
    }
    signalState.waveform_table = id;
    return NULL;
}

antlrcpp::Any STILInterpreter::visitV_inst(STILParser::V_instContext* ctx) {
    pattern_stream << string(padding, ' ');
    list<STILState::Assig> assigs = visit(ctx->assigs());
    signalState.execute_assigs(assigs);
    signalState.clock_cycle(pattern_stream);
    padding = PADDING;
    prev_last_line_index = last_line_index;
    last_line_index = pattern_stream.tellp();
    return NULL;
}

antlrcpp::Any STILInterpreter::visitC_inst(STILParser::C_instContext* ctx) {
    list<STILState::Assig> assigs = visit(ctx->assigs());
    signalState.execute_assigs(assigs);
    return NULL;
}

antlrcpp::Any STILInterpreter::visitF_inst(STILParser::F_instContext* ctx) {
    // We suposse that the STIL program is correct and we just need to
    // treat this instruction as a Condition
    list<STILState::Assig> assigs = visit(ctx->assigs());
    signalState.execute_assigs(assigs);
    return NULL;
}

antlrcpp::Any STILInterpreter::visitCall_inst(STILParser::Call_instContext* ctx) {

    cout << "Saving entire previous state" << endl;
    STILState prev_signalState = signalState;
    signalState.clear_params(); // We clear the possible params from the previous call in the new state (they will be restored on the call's return)

    string id = visit(ctx->id());
    cout << "Calling procedure: " << id << " from block " << contextStack.top().proceds_id << endl;

    if(ctx->assigs() != NULL) {
        list<STILState::Assig> assigs = visit(ctx->assigs());
        signalState.set_params(assigs);
    }

    visit(program.procedures[contextStack.top().proceds_id][id]);

    cout << "Procedure executed. Restoring previous state" << endl;
    signalState = prev_signalState;
    return NULL;
}

antlrcpp::Any STILInterpreter::visitMacro_inst(STILParser::Macro_instContext* ctx) {

    STILState prev_signalState;

    string id = visit(ctx->id());
    cout << "Calling macro: " << id << " from block " << contextStack.top().macros_id << endl;

    if(ctx->assigs() != NULL) {
        cout << "Saving previous params state" << endl;

        prev_signalState = signalState; // We store the previous state in order to be able to restore the params status
        signalState.clear_params();

        list<STILState::Assig> assigs = visit(ctx->assigs());
        signalState.set_params(assigs);
    }

    visit(program.macros[contextStack.top().macros_id][id]);

    cout << "Macro executed. Restoring previous params state" << endl;
    if(ctx->assigs() != NULL) {
        signalState.restore_params(prev_signalState);
    }
    return NULL;
}

antlrcpp::Any STILInterpreter::visitStop_inst(STILParser::Stop_instContext* ctx) {
    cout << "Stopping test" << endl;
    exit(1);
    return NULL;
}

antlrcpp::Any STILInterpreter::visitIddq_inst(STILParser::Iddq_instContext* ctx) {
    cout << "Executing Iddq instruction. Replacing it by the string defined in config" << endl;
    pattern_stream << program.config.iddq_action << endl;
    return NULL;
}

void STILInterpreter::generate_headers() {
    pattern_stream << "opcode_mode=extended;" << endl;
    pattern_stream << "import tset ";
    for(auto it = program.waveFormTables.begin(); it != program.waveFormTables.end(); ++it) {
        if(it != program.waveFormTables.begin()) {
            pattern_stream << ",";
        }
        pattern_stream << "t" << it->second.format(program.config);
    }
    pattern_stream << ";" << endl;
    pattern_stream << "vector($tset";
    for(auto it = program.signals.begin(); it != program.signals.end(); ++it) {
        string formated_id = it->second.format(program.config);
        if(formated_id != "") {
            pattern_stream << "," << formated_id;
        }
    }
    pattern_stream << ")" << endl;
};

void STILInterpreter::insert_halt() {
    pattern_stream.seekp(prev_last_line_index);
    pattern_stream << "halt";
}
