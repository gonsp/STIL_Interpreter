//
// Created by Gonzalo Solera on 04/09/2017.
//

#include "WaveSet.h"

WaveSet::WaveSet(float period, WaveForm& waveform, list<WaveTranslation>& translation_rules) {
    for(auto rule = translation_rules.begin(); rule != translation_rules.end(); ++rule) {
        push_back(WaveDescription(period, waveform, *rule));
    }
}

WaveSet WaveSet::merge(const WaveSet& waveset) const {
    WaveSet merged;
    for(auto i = begin(); i != end(); ++i) {
        for(auto j = waveset.begin(); j != waveset.end(); ++j) {
            pair<bool, WaveDescription> merge_result = i->merge(*j);
            if(merge_result.first) {
                merged.push_back(merge_result.second);
            }
        }
    }
    return merged;
}

string WaveSet::to_string() const {
    string s;
    s += "(";
    for(auto it = begin(); it != end(); ++it) {
        if(it != begin()) {
            s += ", ";
        }
        s += it->to_string();
    }
    s += ")";
    return s;
}
