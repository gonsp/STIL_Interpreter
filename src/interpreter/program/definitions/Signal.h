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

class Signal : public Identifiable {
public:
    signal_dir dir;
    char value;

    Signal() : Identifiable() {}

    Signal(string id, signal_dir dir);
};


#endif //STIL_INTERPRETER_SIGNAL_H
