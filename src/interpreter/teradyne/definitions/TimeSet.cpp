//
// Created by Gonzalo Solera on 03/09/2017.
//

#include "TimeSet.h"

TimeSet::TimeSet(float period) {
    this->period = period;
}

bool TimeSet::merge(const TimeSet& timeset) {
    if(period != timeset.period) {
        return false;
    }
    TimeSet merged_timeset(period);
    for(int i = 0; i < timeset.size(); ++i) {
        WaveSet merged_waveset = (*this)[i].merge(timeset[i]);
        if(merged_waveset.size() == 0) {
            return false;
        }
        merged_timeset.push_back(merged_waveset);
    }
    (*this) = merged_timeset;
    return true;
}
