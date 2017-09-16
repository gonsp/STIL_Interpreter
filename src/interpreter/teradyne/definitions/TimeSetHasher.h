//
// Created by Gonzalo Solera on 15/09/2017.
//

#ifndef STIL_CONVERTER_TIMESETHASHER_H
#define STIL_CONVERTER_TIMESETHASHER_H


#include "TimeSet.h"

using namespace std;

class TimeSetHasher {

private:
    void combine_hash(size_t& hash, size_t next_hash) const;

public:
    size_t operator()(const TimeSet& timeset) const;

    size_t operator()(const WaveSet& waveset) const;

    size_t operator()(const WaveDescription& description) const;
};


#endif //STIL_CONVERTER_TIMESETHASHER_H
