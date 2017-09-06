//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_IDENTIFIABLE_H
#define STIL_INTERPRETER_IDENTIFIABLE_H

#include <string>
#include <iostream>
#include "../teradyne/STILConfig.h"

using namespace std;

class Identifiable {

public:
    string id;

    Identifiable(string id);

    Identifiable();

    string format(STILConfig& config) const;

};


#endif //STIL_INTERPRETER_IDENTIFIABLE_H
