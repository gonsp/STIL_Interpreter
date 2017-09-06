//
// Created by Gonzalo Solera on 04/09/2017.
//

#ifndef STIL_CONVERTER_WAVESET_H
#define STIL_CONVERTER_WAVESET_H

// The set of possible representations for a signal's waveform.
// Here there are stored these options through WaveDescriptions.

#include <list>
#include "WaveDescription.h"
#include "WaveForm.h"


class WaveSet : public list<WaveDescription> {

public:

    WaveSet() {}

    WaveSet(WaveForm& waveform, string& translation_rules);
};


#endif //STIL_CONVERTER_WAVESET_H
