//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_IDENTIFIABLE_H
#define STIL_INTERPRETER_IDENTIFIABLE_H

#include <string>

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

    string id_no_quotes() {
        string id = this->id;
        return id.erase(0, 1).erase(id.size()-1, 1);
    }

};


#endif //STIL_INTERPRETER_IDENTIFIABLE_H
