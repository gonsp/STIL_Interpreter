//
// Created by Gonzalo Solera on 03/09/2017.
//

#ifndef STIL_CONVERTER_STILTIMINGGENERATOR_H
#define STIL_CONVERTER_STILTIMINGGENERATOR_H

#include <vector>
#include <fstream>
#include "TimeSet.h"

using namespace std;

class STILTimingGenerator {

private:
    ofstream output;
    vector<TimeSet> timesets;
    int last_id;

public:

    STILTimingGenerator() {}

    STILTimingGenerator(string timing_file);

    int add_timeset(TimeSet& timeset);

    void finish();
};


#endif //STIL_CONVERTER_STILTIMINGGENERATOR_H
