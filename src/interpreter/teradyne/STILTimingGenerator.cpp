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
    cout << "Adding timeset" << endl;
    for(int id = 0; id < last_id; ++id) {
        cout << "---------------------------------" << endl;
        cout << "Trying to merge it with timeset: " << id << endl;
        if(timesets[id].merge(timeset)) {
            cout << "Merge is done!!" << endl;
//            cache[timeset] = id;
            cout << "Using timeset: " << id << endl;
            return id;
        } else {
            cout << "Merge is not possible" << endl;
        }
        cout << "---------------------------------" << endl;
    }
    timesets.push_back(timeset);
//    cache[timeset] = last_id;
    cout << "Creating timeset: " << last_id << endl;
    return last_id++;
}
