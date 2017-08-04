//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_TIMING_H
#define STIL_INTERPRETER_TIMING_H

#include <unordered_map>
#include "Identifiable.h"
#include "WaveFormTable.h"

class Timing : public Identifiable {

    typedef unordered_map<string, WaveFormTable> WaveFormTables;

public:

    WaveFormTables waveFormTables;

    Timing() : Identifiable() {}

    Timing(string id);
};


#endif //STIL_INTERPRETER_TIMING_H
