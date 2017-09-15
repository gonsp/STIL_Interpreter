//
// Created by Gonzalo Solera on 15/09/2017.
//

#include "TimeSetHasher.h"

size_t TimeSetHasher::operator()(const TimeSet& timeset) const {
//    return hash<string>()(timeset.to_string()); // Very bad results (this was just for debug)
    size_t hash_value = hash<float>()(timeset.period);
    for(int i = 0; i < timeset.wavesets.size(); ++i) {
        combine_hash(hash_value, TimeSetHasher()(timeset.wavesets[i].first));
        combine_hash(hash_value, TimeSetHasher()(timeset.wavesets[i].second));
    }
    return hash_value;
}

size_t TimeSetHasher::operator()(const WaveSet& waveset) const {
    size_t hash_value = hash<int>()(waveset.type);
    for(auto it = waveset.descriptions.begin(); it != waveset.descriptions.end(); ++it) {
        combine_hash(hash_value, TimeSetHasher()(*it));
    }
    return hash_value;
}

size_t TimeSetHasher::operator()(const WaveDescription& description) const {
    size_t hash_value = hash<int>()(description.format);
    for(int i = 0; i < description.edges.size(); ++i) {
        combine_hash(hash_value, hash<float>()(description.edges[i]));
    }
    return hash_value;
}

void TimeSetHasher::combine_hash(size_t& prev, size_t next) const {
    prev ^= (next << 1);
    prev = prev >> 1;
}