//
// Created by Gonzalo Solera on 03/09/2017.
//

#include <cassert>
#include "TimeSet.h"

TimeSet::TimeSet(float period) {
    this->period = period;
}

void TimeSet::add_waveset(const WaveSet& waveset) {
    assert(waveset.type != WaveSet::WaveSetType::UNDEFINED);
    if(waveset.type == WaveSet::WaveSetType::DRIVE) {
        wavesets.push_back(pair<WaveSet, WaveSet>(waveset, WaveSet()));
    } else {
        wavesets.push_back(pair<WaveSet, WaveSet>(WaveSet(), waveset));
    }
}

bool TimeSet::merge(const TimeSet& timeset) {
    if(period != timeset.period) {
        return false;
    }
    TimeSet merged_timeset(period);
    for(int i = 0; i < timeset.wavesets.size(); ++i) {
        WaveSet merged_waveset;
        if(timeset.wavesets[i].first.type != WaveSet::WaveSetType::UNDEFINED) {
            assert(timeset.wavesets[i].first.type == WaveSet::WaveSetType::DRIVE);
            merged_waveset = wavesets[i].first.merge(timeset.wavesets[i].first);
            merged_timeset.wavesets.push_back(pair<WaveSet, WaveSet>(merged_waveset, wavesets[i].second));
        } else {
            assert(timeset.wavesets[i].second.type == WaveSet::WaveSetType::COMPARE);
            merged_waveset = wavesets[i].second.merge(timeset.wavesets[i].second);
            merged_timeset.wavesets.push_back(pair<WaveSet, WaveSet>(wavesets[i].first, merged_waveset));
        }
        if(merged_waveset.descriptions.size() == 0) {
            return false;
        }
    }
    (*this) = merged_timeset;
    return true;
}

string TimeSet::to_string(vector<string> signal_names) const {
    string s;
    s += period;
    s += ", {";
    for(int i = 0; i < wavesets.size(); ++i) {

        const WaveSet& waveset_drive = wavesets[i].first;
        const WaveSet& waveset_compare = wavesets[i].second;

        s += "t" + std::to_string(id);          // TimeSet
        s += "            ";
        s += std::to_string(period);            // Period
        s += "            ";
        s += "1";                               // CPP
        s += "            ";
        s += signal_names[i];                   // Pin Name
        s += "            ";
        s += "i/0";                             // Setup
        s += "            ";
        s += "PAT";                             // Data Source
        s += "            ";
        s += waveset_drive.get_format();        // Data Format
        s += "            ";
        s += waveset_drive.get_drive_on();      // Drive On
        s += "            ";
        s += waveset_drive.get_drive_data();    // Drive Data
        s += "            ";
        s += waveset_drive.get_drive_return();  // Drive Return
        s += "            ";
        s += waveset_drive.get_drive_off();     // Drive Off
        s += "            ";
        s += waveset_compare.get_compare_mode();// Compare Mode
        s += "            ";
        s += waveset_compare.get_compare_open();// Compare Open
        s += "            ";
        s += "Disable";                         // Compare Close
        s += "\n";
    }
    return s;
}

void TimeSet::reduce() {
    for(int i = 0; i < wavesets.size(); ++i) {
        wavesets[i].first.reduce();
        wavesets[i].second.reduce();
    }
}

bool TimeSet::operator==(const TimeSet& other) const {
    return period == other.period && wavesets == other.wavesets;
}