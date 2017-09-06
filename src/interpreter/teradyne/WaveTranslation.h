//
// Created by Gonzalo Solera on 07/09/2017.
//

#ifndef STIL_CONVERTER_WAVETRANSLATION_H
#define STIL_CONVERTER_WAVETRANSLATION_H

#include <string>
#include <vector>

using namespace std;

#define DISABLE -1
#define ANY -2

enum WaveFormat {
    NR, RH, RL, SBH, SBL, SBC, Off, Edge
};

class WaveTranslation {

public:

    typedef pair<bool, float> EdgeRule;

    WaveFormat format;
    vector<EdgeRule> edge_rules;

    WaveTranslation(string rule);
};


#endif //STIL_CONVERTER_WAVETRANSLATION_H
