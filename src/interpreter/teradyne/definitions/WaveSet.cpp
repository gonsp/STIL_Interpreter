//
// Created by Gonzalo Solera on 04/09/2017.
//

#include <assert.h>
#include "WaveSet.h"

WaveSet::WaveSet() {
    type = UNDEFINED;
}

WaveSet::WaveSet(WaveSet::WaveSetType type) {
    this->type = type;
}

WaveSet::WaveSet(float period, WaveForm& waveform, list<WaveTranslation>& translation_rules) {
    type = UNDEFINED;
    for(auto rule = translation_rules.begin(); rule != translation_rules.end(); ++rule) {
        push_back(WaveDescription(period, waveform, *rule));
        WaveSetType last_type = back().format == Edge || back().format == Off ? COMPARE : DRIVE;
        if(type == UNDEFINED) {
            type = last_type;
        } else {
            assert(type == last_type);
        }
    }
}

WaveSet WaveSet::merge(const WaveSet& waveset) const {
    if(type == UNDEFINED) {
        return waveset;
    } else if(waveset.type == UNDEFINED) {
        return *this;
    }
    assert(type == waveset.type);
    WaveSet merged(type);
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

void WaveSet::reduce() {
    erase(++begin(), end());
    front().reduce();
}
