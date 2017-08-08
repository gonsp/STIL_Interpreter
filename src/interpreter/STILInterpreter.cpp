//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <ANTLRInputStream.h>
#include "STILInterpreter.h"
#include "program/STILProgramVisitor.h"

STILInterpreter::STILInterpreter(string stil_file, string pattern_file, string timing_file) {
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
    next_vector = vector<char>(program.signals.size(), ' ');
    visit(program.patternExecs[pattern_exec]);
    cout << "Done" << endl;
}

antlrcpp::Any STILInterpreter::visitPattern_exec(STILParser::Pattern_execContext* ctx) {
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

antlrcpp::Any STILInterpreter::visitLoop(STILParser::LoopContext* ctx) {
    cout << "Executing loop" << endl;
    float times = visit(ctx->int_t());
    while(times > 0) {
        visit(ctx->inst_list());
        --times;
    }
    return NULL;
}

antlrcpp::Any STILInterpreter::visitShift(STILParser::ShiftContext* ctx) {
    return NULL;
}

antlrcpp::Any STILInterpreter::visitW_inst(STILParser::W_instContext* ctx) {
    return NULL;
}

antlrcpp::Any STILInterpreter::visitCall_inst(STILParser::Call_instContext* ctx) {

    cout << "Saving previous state" << endl;
    string prev_waform_table = waveform_table;
    vector<char> prev_vector = next_vector;

    string id = visit(ctx->id());
    cout << "Calling procedure: " << id << " from block " << contextStack.top().proceds_id << endl;

    visit(program.procedures[contextStack.top().proceds_id][id]);

    cout << "Procedure executed. Restoring previous state" << endl;
    waveform_table = prev_waform_table;
    next_vector = prev_vector;
    return NULL;
}

antlrcpp::Any STILInterpreter::visitMacro_inst(STILParser::Macro_instContext* ctx) {
    string id = visit(ctx->id());
    cout << "Calling macro: " << id << " from block " << contextStack.top().macros_id << endl;
    visit(program.macros[contextStack.top().macros_id][id]);
    return NULL;
}

antlrcpp::Any STILInterpreter::visitStop_inst(STILParser::Stop_instContext* ctx) {
    cout << "Stopping test" << endl;
    exit(1);
    return NULL;
}