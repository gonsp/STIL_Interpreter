//
// Created by Gonzalo Solera on 07/08/2017.
//

#ifndef STIL_INTERPRETER_PATTERNCONTEXT_H
#define STIL_INTERPRETER_PATTERNCONTEXT_H

#include <string>

using namespace std;

class PatternContext {

public:

    string proceds_id;
    string macros_id;

    PatternContext() {
        proceds_id = "";
        macros_id = "";
    }

    PatternContext(string proceds_id, string macros_id) {
        this->proceds_id = proceds_id;
        this->macros_id = macros_id;
    }

    PatternContext merge(PatternContext context) {
        PatternContext result = *this;
        if(context.proceds_id != "") {
            result.proceds_id = context.proceds_id;
        }
        if(context.macros_id != "") {
            result.macros_id = context.macros_id;
        }
        return result;
    }
};

class ContextStack : public stack<PatternContext> {

public:

    void push(const PatternContext& context) {
        if(!empty()) {
            stack::push(top().merge(context));
        } else {
            stack::push(context);
        }
    }

    void push(PatternContext&& context) {
        PatternContext aux = context;
        push(aux);
    }
};

#endif //STIL_INTERPRETER_PATTERNCONTEXT_H
