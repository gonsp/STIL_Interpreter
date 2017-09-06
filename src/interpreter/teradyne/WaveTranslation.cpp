//
// Created by Gonzalo Solera on 07/09/2017.
//

#include <sstream>
#include <iostream>
#include "WaveTranslation.h"

WaveTranslation::WaveTranslation(string rule) {
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
            edge_rules.push_back(EdgeRule(false, ANY));
        } else if(s == "-") {
            edge_rules.push_back(EdgeRule(false, DISABLE));
        } else {
            if(s[0] == 'E') {   // It's a reference for the original waveform's edge
                int index = atoi(s.substr(1).c_str());
                edge_rules.push_back(EdgeRule(true, index));
            } else {
                float relative_time = atof(s.c_str());
                edge_rules.push_back(EdgeRule(true, relative_time));
            }
        }
    }
}
