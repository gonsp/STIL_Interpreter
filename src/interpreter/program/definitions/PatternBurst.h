//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_PATTERNBURST_H
#define STIL_INTERPRETER_PATTERNBURST_H

#include <string>
#include <STILParser.h>
#include "Identifiable.h"

using namespace std;
using namespace parser;

class PatternBurst : public Identifiable {

public:

    struct PatternBurstContext {
        string proceds_id;
        string macros_id;

        PatternBurstContext() {}

        PatternBurstContext(string proceds_id, string macros_id) {
            this->proceds_id = proceds_id;
            this->macros_id = macros_id;
        }
    };

    STILParser::Pattern_listContext* ast;
    PatternBurstContext context;

    PatternBurst() : Identifiable() {}

    PatternBurst(string id, STILParser::Pattern_listContext* ast, PatternBurstContext& context);

};


#endif //STIL_INTERPRETER_PATTERNBURST_H
