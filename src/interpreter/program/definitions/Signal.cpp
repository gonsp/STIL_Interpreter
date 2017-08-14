//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <assert.h>
#include "Signal.h"

Signal::Signal(string id, signal_dir dir) : Identifiable(id) {
    this->dir = dir;
}

Signal::Signal(string id, signal_dir dir, signal_scan_dir scan_dir) : Signal(id, dir) {
    this->scan_dir = scan_dir;
}

char Signal::solve_param_ref(string ref_id, char type) {
    auto it = params.find(ref_id);
    if(it == params.end()) {
        it = params.begin();
        if(it == params.end()) {
            return value;
        }
    }

    string& s = it->second;
    assert(s.size() > 0 && "There's a void string in a signal parameter!");

    char wfc = s.front();
    if(type == '#') {
        s.erase(0, 1);
        if(s.size() == 0) {
            params.erase(it);
        }
    }
    return wfc;
}

void Signal::set_padding_to_params(int max_size, char wfc) {
    if(scan_dir != NONE) {
        for(auto it = params.begin(); it != params.end(); ++it) {
            string& values = it->second;
            if(values.size() > 1) { // Avoid modifying used params + signalgroups params
                if(values.size() != max_size) {
                    string padding(max_size - values.size(), wfc);
                    if(scan_dir == SCAN_IN) {
                        values = padding + values;
                    } else if(scan_dir == SCAN_OUT) {
                        values = values + padding;
                    }
                }
            }
        }
    }
}
