//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNAL_H
#define STIL_INTERPRETER_SIGNAL_H

#include <string>
#include <map>
#include "Identifiable.h"

using namespace std;

class Signal : public Identifiable {

public:
    enum signal_dir {
        IN, OUT, INOUT, PSEUDO
    };

    enum signal_scan_dir {
        NONE, SCAN_IN, SCAN_OUT
    };

    class Param : public Identifiable {

    public:
        string values;
        bool needs_refresh = false;

        Param() : Identifiable() {}

        Param(string id, string& values);

        bool refresh();
    };

    typedef unordered_map<string, Param> Params;

    signal_dir dir;
    signal_scan_dir scan_dir = NONE;
    char value = '?';
    Params params;

    Signal() : Identifiable() {}

    Signal(string id, signal_dir dir);

    Signal(string id, signal_dir dir, signal_scan_dir scan_dir);

    char solve_param_ref(string ref_id, char type);

    void set_padding_to_params(int max_size);

    void refresh_params();
};

typedef map<string, Signal> Signals;


#endif //STIL_INTERPRETER_SIGNAL_H
