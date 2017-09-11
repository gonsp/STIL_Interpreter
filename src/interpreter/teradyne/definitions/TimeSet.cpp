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
        wavesets.push_back(pair<WaveSet, WaveSet>(waveset, WaveSet()));
    } else {
        wavesets.push_back(pair<WaveSet, WaveSet>(WaveSet(), waveset));
    }
}

bool TimeSet::merge(const TimeSet& timeset) {
    if(period != timeset.period) {
        return false;
    }
    TimeSet merged_timeset(period);
    for(int i = 0; i < timeset.wavesets.size(); ++i) {
        WaveSet merged_waveset;
        if(timeset.wavesets[i].first.type != WaveSet::WaveSetType::UNDEFINED) {
            assert(timeset.wavesets[i].first.type == WaveSet::WaveSetType::DRIVE);
            merged_waveset = wavesets[i].first.merge(timeset.wavesets[i].first);
            merged_timeset.wavesets.push_back(pair<WaveSet, WaveSet>(merged_waveset, wavesets[i].second));
        } else {
            assert(timeset.wavesets[i].second.type == WaveSet::WaveSetType::COMPARE);
            merged_waveset = wavesets[i].second.merge(timeset.wavesets[i].second);
            merged_timeset.wavesets.push_back(pair<WaveSet, WaveSet>(wavesets[i].first, merged_waveset));
        }
        if(merged_waveset.descriptions.size() == 0) {
            return false;
        }
    }
    (*this) = merged_timeset;
    return true;
}

string TimeSet::to_string() const {
    string s;
    s += period;
    s += ", {";
    for(int i = 0; i < wavesets.size(); ++i) {
        if(i != 0) {
            s += ", ";
        }
        s += "[";
        s += wavesets[i].first.to_string();
        s += " | ";
        s += wavesets[i].second.to_string();
        s += "]";
    }
    s += "}";
    return s;
}

void TimeSet::reduce() {
    for(int i = 0; i < wavesets.size(); ++i) {
        wavesets[i].first.reduce();
        wavesets[i].second.reduce();
    }
}

bool TimeSet::operator==(const TimeSet& other) const {
    return period == other.period && wavesets == other.wavesets;
}

size_t TimeSet::Hasher::operator()(const TimeSet& timeset) const {
    size_t hash_value = hash<float>()(timeset.period);
    for(int i = 0; i < timeset.wavesets.size(); ++i) {
        combine_hash(hash_value, WaveSet::Hasher()(timeset.wavesets[i].first));
        combine_hash(hash_value, WaveSet::Hasher()(timeset.wavesets[i].second));
    }
    return hash_value;
//    return hash<string>()(timeset.to_string());
}

void TimeSet::Hasher::combine_hash(size_t& prev, size_t next) const {
    prev ^= (next << 1);
    prev = prev >> 1;
}
