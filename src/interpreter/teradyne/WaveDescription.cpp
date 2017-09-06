//
// Created by Gonzalo Solera on 04/09/2017.
//

#include "WaveDescription.h"

WaveDescription::WaveDescription(float period, WaveForm& waveform, WaveTranslation& translation) {
    format = translation.format;
    for(int i = 0; i < translation.edge_rules.size(); ++i) {
        WaveTranslation::EdgeRule rule = translation.edge_rules[i];
        if(rule.first) { // It's relative time
            edges.push_back(period * rule.second);
        } else {
            if(rule.second < 0) {
                edges.push_back(rule.second);
            } else {
                edges.push_back(waveform.events[rule.second].time);
            }
        }
    }
}
