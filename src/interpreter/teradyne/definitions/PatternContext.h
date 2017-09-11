//
// Created by Gonzalo Solera on 07/08/2017.
//

#ifndef STIL_INTERPRETER_PATTERNCONTEXT_H
#define STIL_INTERPRETER_PATTERNCONTEXT_H

#include <string>
#include <stack>

using namespace std;

class PatternContext {

public:

    string proceds_id;
    string macros_id;

    PatternContext();

    PatternContext(string proceds_id, string macros_id);

    PatternContext merge(PatternContext context);
};

class ContextStack : public stack<PatternContext> {

public:

    void push(const PatternContext& context);

    void push(PatternContext&& context);
};

#endif //STIL_INTERPRETER_PATTERNCONTEXT_H
