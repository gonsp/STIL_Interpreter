//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_STILPROGRAM_H
#define STIL_INTERPRETER_STILPROGRAM_H

#include <string>
#include <map>
#include <tree/ParseTree.h>
#include "definitions/Signal.h"
#include "definitions/Timing.h"
#include "definitions/PatternBurst.h"
#include "definitions/PatternExec.h"
#include "definitions/Pattern.h"
#include "definitions/Procedure.h"
#include "definitions/Macro.h"

using namespace std;
using namespace antlr4;
using namespace tree;

#define GLOBAL_DEF "global"

class STILProgram {
    typedef map<string, PatternExec> PatternExecs;
    typedef map<string, PatternBurst> PatternBursts;
    typedef map<string, Pattern> Patterns;
    typedef map<string, Procedure> Procedures;
    typedef map<string, Macro> Macros;
    typedef map<string, Signal> Signals;
    typedef map<string, Timing> Timings;

public:
    PatternExecs patternExecs;
    PatternBursts patternBursts;
    Patterns patterns;
    Procedures procedures;
    Macros macros;
    Signals signals;
    Timings timings;

    STILProgram();
};


#endif //STIL_INTERPRETER_STILPROGRAM_H
