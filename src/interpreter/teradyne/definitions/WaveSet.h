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
#include "WaveTranslation.h"


class WaveSet : public list<WaveDescription> {

public:

    WaveSet() {}

    WaveSet(float period, WaveForm& waveform, list<WaveTranslation>& translation_rules);

    WaveSet merge(const WaveSet& waveset) const;

    string to_string() const;
};


#endif //STIL_CONVERTER_WAVESET_H
