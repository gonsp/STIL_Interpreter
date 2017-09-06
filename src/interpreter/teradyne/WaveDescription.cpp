//
// Created by Gonzalo Solera on 04/09/2017.
//

#include <sstream>
#include "WaveDescription.h"


WaveDescription::WaveDescription(WaveForm& waveform, string& rule) {
    istringstream iss(rule);
    string s;
    getline(iss, s, ',');
    if(s == "NR") {
        format = NR;
    } else if(s == "RH") {
        format = RH;
    } else if(s == "RL") {
        format = RL;
    } else if(s == "SBH") {
        format = SBH;
    } else if(s == "SBL") {
        format = SBL;
    } else if(s == "SBC") {
        format = SBC;
    } else if(s == "Off") {
        format = Off;
    } else if(s == "Edge") {
        format = Edge;
    } else {
        cerr << "Error parsing: " << rule << " from config file" << endl;
        exit(1);
    }
    while(iss >> s) {           // Edge number
        iss >> s;               // Equal symbol
        getline(iss, s, ',');   // Time value
        s.erase(0, 1);
        if(s == "?") {
            edges.push_back(ANY);
        } else if(s == "-") {
            edges.push_back(DISABLE);
        } else {
            if(s[0] == 'E') {   // It's a reference for the original waveform's edge
                string index = s.substr(1);
                edges.push_back(waveform.events[atoi(index.c_str())].time);
            } else {
                edges.push_back(atof(s.c_str()));
            }
        }
    }
}
