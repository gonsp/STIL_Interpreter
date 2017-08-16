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
    if(it == params.end()) { // There is no param by name
        it = params.begin(); // Retrieving param by content (any other param)
        if(it == params.end()) { // There is no other param, return last assigned value
            return value;
        }
    }

    string& s = it->second.values;
    if(s.size() == 0) {
        cerr << "There's a void string in a signal parameter!" << endl;
        cerr << "Signal: " << id << ", parameter name: " << it->second.id << endl;
        exit(1);
    }

    char wfc = s.front();
    if(type == '#') {
        it->second.needs_refresh = true;
    }
    return wfc;
}

void Signal::set_padding_to_params(int max_size) {
    if(scan_dir != NONE) {
        for(auto it = params.begin(); it != params.end(); ++it) {
            string& values = it->second.values;
            if(values.size() > 1) { // Avoid modifying used params + signalgroups params
                if(values.size() != max_size) {
                    if(scan_dir == SCAN_IN) {
                        string padding(max_size - values.size(), '$');
                        values = padding + values;
                    } else if(scan_dir == SCAN_OUT) {
                        string padding(max_size - values.size(), '@');
                        values = values + padding;
                    }
                }
            }
        }
    }
}

void Signal::refresh_params() {
    auto it = params.begin();
    while(it != params.end()) {
        bool is_empty = it->second.refresh();
        if(is_empty) {
            it = params.erase(it);
        } else {
            ++it;
        }
    }
}

Signal::Param::Param(string id, string& values) : Identifiable(id) {
    this->values = values;
    needs_refresh = false;
    assert(values.size() != 0);
}

bool Signal::Param::refresh() {
    if(needs_refresh) {
        needs_refresh = false;
        values.erase(0, 1);
        if(values.size() == 0) {
            return true;
        }
    }
    return false;
}
