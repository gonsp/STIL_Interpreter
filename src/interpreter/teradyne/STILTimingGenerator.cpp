//
// Created by Gonzalo Solera on 03/09/2017.
//

#include "STILTimingGenerator.h"

STILTimingGenerator::STILTimingGenerator(string timing_file) {
    output.open(timing_file);
}

void STILTimingGenerator::finish() {
    output.close();
}

int STILTimingGenerator::add_timeset(const TimeSet& timeset) {
//    if(cache.count(timeset) != 0) {
//        return cache[timeset];
//    }
    for(int id = 0; id < timesets.size(); ++id) {
        if(timesets[id].merge(timeset)) {
//            cache[timeset] = id;
            return id;
        }
    }
    cout << "Creating timeset: " << timesets.size() << endl;
    timesets.push_back(timeset);
//    cache[timeset] = last_id;
    return timesets.size();
}
