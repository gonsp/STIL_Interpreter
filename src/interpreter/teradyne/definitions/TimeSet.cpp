//
// Created by Gonzalo Solera on 03/09/2017.
//

#include <cassert>
#include "TimeSet.h"

TimeSet::TimeSet(float period) {
    this->period = period;
}

void TimeSet::add_waveset(const WaveSet& waveset) {
    assert(waveset.type != WaveSet::WaveSetType::UNDEFINED);
    if(waveset.type == WaveSet::WaveSetType::DRIVE) {
        push_back(pair<WaveSet, WaveSet>(waveset, WaveSet()));
    } else {
        push_back(pair<WaveSet, WaveSet>(WaveSet(), waveset));
    }
}

bool TimeSet::merge(const TimeSet& timeset) {
    if(period != timeset.period) {
        return false;
    }
    TimeSet merged_timeset(period);
    for(int i = 0; i < timeset.size(); ++i) {
        WaveSet merged_waveset;
        if(timeset[i].first.type != WaveSet::WaveSetType::UNDEFINED) {
            merged_waveset = at(i).first.merge(timeset[i].first);
        } else {
            merged_waveset = at(i).second.merge(timeset[i].second);
        }
        if(merged_waveset.size() == 0) {
            return false;
        }
        merged_timeset.add_waveset(merged_waveset);
    }
    (*this) = merged_timeset;
    return true;
}

string TimeSet::to_string() const {
    string s;
    s += "{";
    for(int i = 0; i < size(); ++i) {
        if(i != 0) {
            s += ", ";
        }
        s += "[";
        s += at(i).first.to_string();
        s += " | ";
        s += at(i).second.to_string();
        s += "]";
    }
    s += "}";
    return s;
}

void TimeSet::reduce() {
    for(int i = 0; i < size(); ++i) {
        at(i).first.reduce();
        at(i).second.reduce();
    }
}
