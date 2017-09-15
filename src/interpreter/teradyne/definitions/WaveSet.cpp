//
// Created by Gonzalo Solera on 04/09/2017.
//

#include <assert.h>
#include "WaveSet.h"

WaveSet::WaveSet() {
    type = UNDEFINED;
}

WaveSet::WaveSet(WaveSetType type) {
    this->type = type;
}

WaveSet::WaveSet(float period, WaveForm& waveform, list<WaveTranslation>& translation_rules) {
    type = UNDEFINED;
    for(auto rule = translation_rules.begin(); rule != translation_rules.end(); ++rule) {
        descriptions.push_back(WaveDescription(period, waveform, *rule));
        WaveSetType last_type = descriptions.back().format == Edge || descriptions.back().format == Off ? COMPARE : DRIVE;
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
    for(auto i = descriptions.begin(); i != descriptions.end(); ++i) {
        for(auto j = waveset.descriptions.begin(); j != waveset.descriptions.end(); ++j) {
            pair<bool, WaveDescription> merge_result = i->merge(*j);
            if(merge_result.first) {
                merged.descriptions.push_back(merge_result.second);
            }
        }
    }
    return merged;
}

string WaveSet::to_string() const {
    string s;
    s += "(";
    for(auto it = descriptions.begin(); it != descriptions.end(); ++it) {
        if(it != descriptions.begin()) {
            s += ", ";
        }
        s += it->to_string();
    }
    s += ")";
    return s;
}

void WaveSet::reduce() {
    assert(type == UNDEFINED || descriptions.size() > 0);
    if(type != UNDEFINED) {
        descriptions.erase(++descriptions.begin(), descriptions.end());
        descriptions.front().reduce();
    }
}

bool WaveSet::operator==(const WaveSet& other) const {
    return type == other.type && descriptions == other.descriptions;
}
