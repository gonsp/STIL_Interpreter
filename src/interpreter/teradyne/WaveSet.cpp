//
// Created by Gonzalo Solera on 04/09/2017.
//

#include <sstream>
#include "WaveSet.h"

WaveSet::WaveSet(WaveForm& waveform, string& translation_rules) {
    istringstream iss(translation_rules);
    char c;
    while(iss >> c) {   // It's a "coma"
        iss >> c;       // It's a left parenthesis
        string rule;    // It's a full rule
        getline(iss, rule, ')');
        push_back(WaveDescription(waveform, rule));
    }
}
