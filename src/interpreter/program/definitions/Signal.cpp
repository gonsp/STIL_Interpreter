//
// Created by Gonzalo Solera on 03/08/2017.
//

#include <assert.h>
#include "Signal.h"

Signal::Signal(string id, signal_dir dir) : Identifiable(id) {
    this->dir = dir;
}

char Signal::solve_param_ref(string ref_id, char type) {
    auto it = params.find(ref_id);
    if(it == params.end()) {
        it = params.begin();
        assert(it != params.end());
    }

    string& s = it->second;
    assert(s.size() >= 0);

    char wfc = s.front();
    if(type == '#') {
        s.erase(0, 1);
    }
    return wfc;
}
