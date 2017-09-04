//
// Created by Gonzalo Solera on 03/09/2017.
//

#ifndef STIL_CONVERTER_STILTIMINGGENERATOR_H
#define STIL_CONVERTER_STILTIMINGGENERATOR_H

#include <vector>
#include <fstream>
#include "program/definitions/TimeSet.h"

using namespace std;

class STILTimingGenerator {

private:
    ofstream output;
    vector<TimeSet> timesets;

public:

    STILTimingGenerator() {}

    STILTimingGenerator(string timing_file);

    void finish();
};


#endif //STIL_CONVERTER_STILTIMINGGENERATOR_H
