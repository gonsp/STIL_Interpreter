//
// Created by Gonzalo Solera on 04/09/2017.
//

#ifndef STIL_CONVERTER_WAVESET_H
#define STIL_CONVERTER_WAVESET_H

// The set of possible representations for a signal's waveform.
// Here there are stored these options through WaveDescriptions.

#include "WaveDescription.h"

class WaveSet : public vector<WaveDescription> {

public:

    WaveSet() {}

    WaveSet(string s);
};


#endif //STIL_CONVERTER_WAVESET_H
