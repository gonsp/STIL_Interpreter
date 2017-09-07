//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_PATTERNBURST_H
#define STIL_INTERPRETER_PATTERNBURST_H

#include <string>
#include <STILParser.h>
#include "Identifiable.h"
#include "../../PatternContext.h"

using namespace std;
using namespace parser;

class PatternBurst : public Identifiable {

public:

    STILParser::Pattern_listContext* ast;
    PatternContext context;

    PatternBurst() : Identifiable() {}

    PatternBurst(string id, STILParser::Pattern_listContext* ast, PatternContext& context);

};

typedef unordered_map<string, PatternBurst> PatternBursts;

#endif //STIL_INTERPRETER_PATTERNBURST_H
