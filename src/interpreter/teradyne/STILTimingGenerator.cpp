//
// Created by Gonzalo Solera on 03/09/2017.
//

#include "STILTimingGenerator.h"

STILTimingGenerator::STILTimingGenerator(string timing_file) {
    output.open(timing_file);
}

void STILTimingGenerator::finish() {
    for(int id = 0; id < timesets.size(); ++id) {
        timesets[id].reduce();
        output << id << "       " << timesets[id].to_string() << endl;
    }
    output.close();
}

int STILTimingGenerator::add_timeset(const TimeSet& timeset) {
    int max = 0;
    for(int i = 0; i < cache.bucket_count(); ++i) {
        int count = cache.bucket_size(i);
        cout << count << endl;
        if(count > max) {
            max = count;
        }
    }
    cout << "%%%%%%%%%%%%%%%% max elements in bucket: " << max << endl;
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
    timesets.push_back(timeset);
    cache[timeset] = id;
    return id;
}
