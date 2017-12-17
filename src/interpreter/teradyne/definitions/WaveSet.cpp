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

string WaveSet::get_format() const {
    assert(descriptions.size() == 1);
    return descriptions.front().get_format();
}

string WaveSet::get_drive_on() const {
    assert(type == DRIVE);
    return std::to_string(descriptions.front().edges[0]);
}

string WaveSet::get_drive_data() const {
    assert(type == DRIVE);
    return std::to_string(descriptions.front().edges[1]);
}

string WaveSet::get_drive_return() const {
    assert(type == DRIVE);
    return std::to_string(descriptions.front().edges[2]);
}

string WaveSet::get_drive_off() const {
    assert(type == DRIVE);
    return std::to_string(descriptions.front().edges[3]);
}

string WaveSet::get_compare_mode() const {
    return get_format();
}

string WaveSet::get_compare_open() const {
    assert(type == COMPARE);
    return std::to_string(descriptions.front().edges[0]);
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
