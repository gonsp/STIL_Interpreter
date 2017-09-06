//
// Created by Gonzalo Solera on 04/09/2017.
//

#include "WaveSet.h"

WaveSet::WaveSet(float period, WaveForm& waveform, list<WaveTranslation>& translation_rules) {
    for(auto rule = translation_rules.begin(); rule != translation_rules.end(); ++rule) {
        push_back(WaveDescription(period, waveform, *rule));
    }
}
