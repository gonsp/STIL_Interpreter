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
//    if(cache.count(timeset) != 0) {
//        return cache[timeset];
//    }
    cout << "------------------------------------" << endl;
    cout << "Adding timeset: " << timeset.period;
    for(int i = 0; i < timeset.wavesets.size(); ++i) {
        cout << timeset.wavesets[i].descriptions.size() << ", ";
    }
    cout << endl;
    for(int id = 0; id < last_id; ++id) {
        cout << "Trying to merge with timeset: " << timeset.period;
        for(int i = 0; i < timeset.wavesets.size(); ++i) {
            cout << timeset.wavesets[i].descriptions.size() << ", ";
        }
        cout << endl;
        if(timesets[id].merge(timeset)) {
//            cache[timeset] = id;
            cout << "%%%%%%%%%%%%%%Using timeset: " << id << endl;
            return id;
        }
    }
    cout << "==============Creating timeset: " << last_id << endl;
    timesets.push_back(timeset);
    cout << "------------------------------------" << endl;
//    cache[timeset] = last_id;
    return last_id++;
}
