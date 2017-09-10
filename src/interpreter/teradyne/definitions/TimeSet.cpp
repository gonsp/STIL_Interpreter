//
// Created by Gonzalo Solera on 03/09/2017.
//

#include "TimeSet.h"

TimeSet::TimeSet(float period) {
    this->period = period;
}

bool TimeSet::merge(const TimeSet& timeset) {
    vector<WaveSet> merged_wavesets;
    for(int i = 0; i < timeset.wavesets.size(); ++i) {
        WaveSet merged_waveset = wavesets[i].merge(timeset.wavesets[i]);
        if(merged_waveset.descriptions.size() == 0) {
            return false;
        }
        merged_wavesets.push_back(merged_waveset);
    }
    wavesets = merged_wavesets;
    return true;
}
