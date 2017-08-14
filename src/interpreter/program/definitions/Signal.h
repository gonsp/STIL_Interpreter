//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNAL_H
#define STIL_INTERPRETER_SIGNAL_H

#include <string>
#include "Identifiable.h"

using namespace std;

enum signal_dir {
    IN, OUT, INOUT
};

enum signal_scan_dir {
    NONE, SCAN_IN, SCAN_OUT
};

class Signal : public Identifiable {

public:
    typedef unordered_map<string, string> Params;

    signal_dir dir;
    signal_scan_dir scan_dir = NONE;
    char value = '?';
    Params params;

    Signal() : Identifiable() {}

    Signal(string id, signal_dir dir);

    char solve_param_ref(string ref_id, char type);

    void set_padding_to_params(int max_size, char wfc);
};


#endif //STIL_INTERPRETER_SIGNAL_H
