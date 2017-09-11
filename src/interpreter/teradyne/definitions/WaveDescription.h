//
// Created by Gonzalo Solera on 04/09/2017.
//

#ifndef STIL_CONVERTER_WAVEDESCRIPTION_H
#define STIL_CONVERTER_WAVEDESCRIPTION_H

#include <vector>
#include <string>
#include "WaveForm.h"

using namespace std;

// A WaveDescription is an specific possible description of a waveform. It's important to note that a single WaveDescription could
// refer to multiple ways of representing that specific waveform if an edge's time is not specified.

class WaveDescription {

public:
    WaveFormat format;
    vector<float> edges;

    WaveDescription() {}

    WaveDescription(float period, WaveForm& waveform, WaveTranslation& rule);

    pair<bool, WaveDescription> merge(const WaveDescription& description) const;

    void reduce();

    string to_string() const;

    bool operator==(const WaveDescription& description) const;
};


#endif //STIL_CONVERTER_WAVEDESCRIPTION_H
