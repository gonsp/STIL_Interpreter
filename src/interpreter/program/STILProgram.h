//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAM_H
#define STIL_INTERPRETER_STILPROGRAM_H

#include <string>
#include <unordered_map>
#include <tree/ParseTree.h>
#include <STILParser.h>
#include "definitions/Signal.h"
#include "definitions/SignalGroup.h"
#include "definitions/PatternBurst.h"
#include "definitions/WaveFormTable.h"
#include "definitions/STILConfig.h"

using namespace std;
using namespace antlr4;
using namespace tree;
using namespace parser;

#define GLOBAL_DEF "global"

typedef unordered_map<string, STILParser::Pattern_execContext*> PatternExecs;
typedef unordered_map<string, PatternBurst> PatternBursts;
typedef unordered_map<string, STILParser::Inst_listContext*> Patterns;
typedef unordered_map<string, STILParser::Inst_listContext*> Procedures;
typedef unordered_map<string, STILParser::Inst_listContext*> Macros;
typedef unordered_map<string, Procedures> ProceduresContexts;
typedef unordered_map<string, Macros> MacrosContexts;
typedef unordered_map<string, Signal> Signals;
typedef unordered_map<string, SignalGroup> SignalGroups;
typedef unordered_map<string, WaveFormTable> WaveFormTables;

class STILProgram {

public:
    PatternExecs patternExecs;
    PatternBursts patternBursts;
    Patterns patterns;
    ProceduresContexts procedures;
    MacrosContexts macros;
    Signals signals;
    SignalGroups signalGroups;
    WaveFormTables waveFormTables;

    STILConfig config;

    STILProgram(STILConfig config) {
        this->config = config;
    }
};


#endif //STIL_INTERPRETER_STILPROGRAM_H
