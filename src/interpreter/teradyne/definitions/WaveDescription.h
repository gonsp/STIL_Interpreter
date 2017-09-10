//
// Created by Gonzalo Solera on 04/09/2017.
//

#ifndef STIL_CONVERTER_WAVEDESCRIPTION_H
#define STIL_CONVERTER_WAVEDESCRIPTION_H

#include <vector>
#include <string>
#include "WaveForm.h"

using namespace std;

// A WaveDescription is an specific possible description of a waveform. It's important to note that a single WaveDescription could
// refer to multiple ways of representing that specific waveform if an edge's time is not specified.

class WaveDescription {

public:
    WaveFormat format;
    vector<float> edges;

    WaveDescription() {}

    WaveDescription(float period, WaveForm& waveform, WaveTranslation& rule);

    pair<bool, WaveDescription> merge(const WaveDescription& description) const {
        pair<bool, WaveDescription> merged(false, WaveDescription());
        if(format != description.format) {
        	return merged;
        }
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
};


#endif //STIL_CONVERTER_WAVEDESCRIPTION_H
