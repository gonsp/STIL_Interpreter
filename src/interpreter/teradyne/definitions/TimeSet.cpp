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
        merged_timeset.id = this->id;
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

#define MARGIN 15
#define FORMAT(level) s += string(level*MARGIN - s.size(), ' ');

string TimeSet::to_string(vector<string> signal_names) const {
    string output;
    for(int i = 0; i < wavesets.size(); ++i) {

        const WaveSet& waveset_drive = wavesets[i].first;
        const WaveSet& waveset_compare = wavesets[i].second;

        string s;
        s += "t" + std::to_string(id);          // TimeSet
        FORMAT(1)
        s += std::to_string(period);            // Period
        FORMAT(2)
        s += "1";                               // CPP
        FORMAT(3)
        s += signal_names[i];                   // Pin Name
        FORMAT(4)
        s += "i/0";                             // Setup
        FORMAT(5)
        s += "PAT";                             // Data Source
        FORMAT(6)
        s += waveset_drive.get_format();        // Data Format
        FORMAT(7)
        s += waveset_drive.get_drive_on();      // Drive On
        FORMAT(8)
        s += waveset_drive.get_drive_data();    // Drive Data
        FORMAT(9)
        s += waveset_drive.get_drive_return();  // Drive Return
        FORMAT(10)
        s += waveset_drive.get_drive_off();     // Drive Off
        FORMAT(11)
        s += waveset_compare.get_compare_mode();// Compare Mode
        FORMAT(12)
        s += waveset_compare.get_compare_open();// Compare Open
        FORMAT(13)
        s += "Disable";                         // Compare Close
        s += "\n";

        output += s;
    }
    return output;
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