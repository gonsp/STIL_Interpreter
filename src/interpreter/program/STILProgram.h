//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAM_H
#define STIL_INTERPRETER_STILPROGRAM_H

#include <string>
#include <unordered_map>
#include <tree/ParseTree.h>
#include "definitions/Signal.h"
#include "definitions/Timing.h"
#include "definitions/PatternBurst.h"
#include "definitions/PatternExec.h"
#include "definitions/Pattern.h"
#include "definitions/Procedure.h"
#include "definitions/Macro.h"
#include "definitions/SignalGroup.h"

using namespace std;
using namespace antlr4;
using namespace tree;

#define GLOBAL_DEF "global"

class STILProgram {
    typedef unordered_map<string, PatternExec> PatternExecs;
    typedef unordered_map<string, PatternBurst> PatternBursts;
    typedef unordered_map<string, Pattern> Patterns;
    typedef unordered_map<string, Procedure> Procedures;
    typedef unordered_map<string, Macro> Macros;
    typedef unordered_map<string, Signal> Signals;
    typedef unordered_map<string, SignalGroup> SignalGroups;
    typedef unordered_map<string, Timing> Timings;

public:
    PatternExecs patternExecs;
    PatternBursts patternBursts;
    Patterns patterns;
    Procedures procedures;
    Macros macros;
    Signals signals;
    SignalGroups signalGroups;
    Timings timings;
};


#endif //STIL_INTERPRETER_STILPROGRAM_H
