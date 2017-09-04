//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_IDENTIFIABLE_H
#define STIL_INTERPRETER_IDENTIFIABLE_H

#include <string>
#include "STILConfig.h"
#include <iostream>

using namespace std;

class Identifiable {

public:
    string id;

    Identifiable(string id) {
        this->id = id;
    }

    Identifiable() {
        id = string("_unitialized_");
    }

    string format(STILConfig& config) const {
        string id = this->id;

        if(config.namesMap.find(id) != config.namesMap.end()) {
            return config.namesMap[id];
        }

        id.erase(0, 1);
        id.pop_back();

        if(config.removeBrackets) {
            for(int i = 0; i < id.size(); ++i) {
                if(id[i] == '[') {
                    for(int j = i+1; j < id.size(); ++j) {
                        if(id[j] == ']') {
                            string name = id.substr(0, i);
                            string index = id.substr(i+1, j-i-1);
                            return name + "_" + index;
                        }
                    }
                }
            }
        }
        return id;
    }

};


#endif //STIL_INTERPRETER_IDENTIFIABLE_H
