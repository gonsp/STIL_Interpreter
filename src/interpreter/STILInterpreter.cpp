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
    run(GLOBAL_DEF);
}

void STILInterpreter::run(string pattern_exec) {
    ANTLRInputStream input(stil_input);
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    cout << "Starting file parsing" << endl;
    STILParser parser(&tokens);
    ParseTree* ast = parser.program();
    cout << "File parsed successfully" << endl;

    cout << "Generating internal representation of the program" << endl;
    STILProgramVisitor programVisitor(program);
    programVisitor.visit(ast);
    cout << "Generation successful" << endl;

    cout << "Starting interpretation" << endl;
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
            cout << "With explicit context" << endl;
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
    return STILBaseVisitor::visitPattern_list(ctx);
}
