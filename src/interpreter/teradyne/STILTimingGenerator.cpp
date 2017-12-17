//
// Created by Gonzalo Solera on 03/09/2017.
//

#include "STILTimingGenerator.h"

STILTimingGenerator::STILTimingGenerator(string timing_file) {
    output.open(timing_file);
}

void STILTimingGenerator::finish(vector<string> signal_names) {
    for(int id = 0; id < timesets.size(); ++id) {
        timesets[id].reduce();
        output << timesets[id].to_string(signal_names) << endl;
    }
    output.close();
}

int STILTimingGenerator::add_timeset(TimeSet& timeset) {
    auto it = cache.find(timeset);
    if(it != cache.end()) {
        return it->second;
    }
    for(int id = 0; id < timesets.size(); ++id) {
        if(timesets[id].merge(timeset)) {
            cache[timeset] = id;
            return id;
        }
    }
    int id = timesets.size();
    cout << "Creating timeset: " << id << endl;
    timeset.id = id;
    timesets.push_back(timeset);
    cache[timeset] = id;
    return id;
}
