//
// Created by Gonzalo Solera on 03/09/2017.
//

#include "STILTimingGenerator.h"

STILTimingGenerator::STILTimingGenerator(string timing_file) {
    last_id = 0;
    output.open(timing_file);
}

void STILTimingGenerator::finish() {
    output.close();
}

int STILTimingGenerator::add_timeset(TimeSet& timeset) {
    return last_id++;
}
