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


class WaveSet {

public:

    enum WaveSetType {
        DRIVE, COMPARE, UNDEFINED
    };

    WaveSetType type;
    list<WaveDescription> descriptions;

    WaveSet();

    WaveSet(WaveSetType type);

    WaveSet(float period, WaveForm& waveform, list<WaveTranslation>& translation_rules);

    WaveSet merge(const WaveSet& waveset) const;

    void reduce();

    string to_string() const;

    string get_format() const;

    string get_drive_on() const;

    string get_drive_data() const;

    string get_drive_return() const;

    string get_drive_off() const;

    string get_compare_mode() const;

    string get_compare_open() const;

    bool operator==(const WaveSet& waveset) const;
};


#endif //STIL_CONVERTER_WAVESET_H
