//
// Created by Gonzalo Solera on 03/08/2017.
//

#ifndef STIL_INTERPRETER_SIGNAL_H
#define STIL_INTERPRETER_SIGNAL_H

#include <string>
using namespace std;

class Signal {
public:
    enum signal_dir {
        IN, OUT, INOUT
    };

    string id;
    signal_dir dir;
};


#endif //STIL_INTERPRETER_SIGNAL_H
