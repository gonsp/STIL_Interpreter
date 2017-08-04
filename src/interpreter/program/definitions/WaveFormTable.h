//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_WAVEFORMTABLE_H
#define STIL_INTERPRETER_WAVEFORMTABLE_H

#include "Identifiable.h"

class WaveFormTable : public Identifiable {

public:

    float period;

    WaveFormTable() : Identifiable() {}

    WaveFormTable(string id, float period);

};


#endif //STIL_INTERPRETER_WAVEFORMTABLE_H
