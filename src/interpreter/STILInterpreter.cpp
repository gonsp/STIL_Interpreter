//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <ANTLRInputStream.h>
#include <STILFilePreprocessor.h>
#include "STILInterpreter.h"
#include "program/STILProgramVisitor.h"

STILInterpreter::STILInterpreter(string stil_file, string pattern_file, string timing_file, STILConfig& config) : program(config) {
    this->stil_file = stil_file;
    this->pattern_file = pattern_file;
    this->timing_file = timing_file;

    STILFilePreprocessor::preprocess(stil_file);

    stil_input.open(stil_file + ".tmp");
}

void STILInterpreter::run() {
    cout << "Running default pattern_exec block" << endl;
    cout << "(You can specify the pattern_exec block with an additional argument)" << endl;
    run(GLOBAL_DEF);
}

void STILInterpreter::run(string pattern_exec) {

    cout << "--------------------------------------" << endl;

    cout << "Starting file parsing" << endl;
    ANTLRInputStream input(stil_input);
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

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
    actual_line = 0;
    signalState = STILState(&program, &actual_line);
    patternGenerator = STILPatternGenerator(pattern_file, &program, &actual_line);
    timingGenerator = STILTimingGenerator(timing_file);

    visit(program.patternExecs[pattern_exec]);

    patternGenerator.finish();
    timingGenerator.finish();

    string aux = stil_file + ".tmp";
    remove(aux.c_str()); // Removing the temporal preprocessed file
    cout << "Done" << endl;
}

antlrcpp::Any STILInterpreter::visitPattern_exec(STILParser::Pattern_execContext* ctx) {
    patternGenerator.print_headers();
    contextStack.push(PatternContext()); // Base context
    for(int i = 0; i < ctx->pattern_burst_call().size(); ++i) {
        visit(ctx->pattern_burst_call(i));
        assert(contextStack.size() == 1); // Needs to remain just the base context
    }
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

antlrcpp::Any STILInterpreter::visitInst(STILParser::InstContext* ctx) {
    actual_line = (int) ctx->getStart()->getLine();
    visitChildren(ctx);
    return NULL;
}

antlrcpp::Any STILInterpreter::visitLoop(STILParser::LoopContext* ctx) {
    cout << actual_line << ": " << "Executing loop" << endl;
    int times = visit(ctx->int_t());
    if(ctx->inst_list()->children.size() == 1) {
        string s = "repeat " + to_string(times);
        patternGenerator.print_tester_inst(s);
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
    cout << actual_line << ": " << "Executing shift" << endl;
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
    if(id != signalState.active_table.id) {
        cout << "Changing active waveform_table to: " << id << endl;
    }
    signalState.active_table = id;
    return NULL;
}

antlrcpp::Any STILInterpreter::visitV_inst(STILParser::V_instContext* ctx) {
    list<STILState::Assig> assigs = visit(ctx->assigs());
    signalState.execute_assigs(assigs);
    patternGenerator.clock_cycle(signalState, timingGenerator);
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
    string id = visit(ctx->id());
    cout << actual_line << ": " << "Calling procedure: " << id << " from block " << contextStack.top().proceds_id << endl;

    cout << "Saving entire previous state" << endl;
    STILState prev_signalState = signalState;
    signalState.clear_params(); // We clear the possible params from the previous call in the new state (they will be restored on the call's return)

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
    string id = visit(ctx->id());
    cout << actual_line << ": " << "Calling macro: " << id << " from block " << contextStack.top().macros_id << endl;

    STILState prev_signalState;

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
    cout << actual_line << ": " << "Stopping test" << endl;
    exit(1);
    return NULL;
}

antlrcpp::Any STILInterpreter::visitIddq_inst(STILParser::Iddq_instContext* ctx) {
    cout << actual_line << ": " << "Executing Iddq instruction. Replacing it by the string defined in config" << endl;
    patternGenerator.print_iddq();
    return NULL;
}