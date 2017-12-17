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

pair<bool, WaveDescription> WaveDescription::merge(const WaveDescription& description) const {
    pair<bool, WaveDescription> merged(false, WaveDescription());
    if(format != description.format) {
        return merged;
    }
    merged.second.format = format;
    for(int i = 0; i < edges.size(); ++i) {
        const float& a = edges[i];
        const float& b = description.edges[i];
        if(a == b) {
            merged.second.edges.push_back(a);
        } else {
            if(a == DISABLE || b == DISABLE) {
                return merged;
            }
            if(a == ANY) {
                merged.second.edges.push_back(b);
            } else if(b == ANY) {
                merged.second.edges.push_back(a);
            } else {
                return merged;
            }
        }
    }
    merged.first = true;
    return merged;
}

string WaveDescription::to_string() const {
    string s;
    s += "[";
    s += std::to_string(format);
    s += ": ";
    for(int i = 0; i < edges.size(); ++i) {
        if(i != 0) {
            s += ", ";
        }
        if(edges[i] == DISABLE) {
            s += " - ";
        } else {
            s += std::to_string(edges[i]);
        }
    }
    s += "]";
    return s;
}

string WaveDescription::get_format() const {
    if(format == NR) {
        return "NR";
    } else if(format == RH) {
        return "RH";
    } else if(format == RL) {
        return "RL";
    } else if(format == SBH) {
        return "SBH";
    } else if(format == SBL) {
        return "SBL";
    } else if(format == SBC) {
        return "SBC";
    } else if(format == Off) {
        return "Off";
    } else if(format == Edge) {
        return "Edge";
    } else {
        return "";
    }
}

void WaveDescription::reduce() {
    for(int i = 0; i < edges.size(); ++i) {
        if(edges[i] == ANY) {
            edges[i] = i > 0 ? edges[i-1] : 0;
        }
    }
}

bool WaveDescription::operator==(const WaveDescription& other) const {
    return format == other.format && edges == other.edges;
}
