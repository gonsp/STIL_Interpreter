#include "Identifiable.h"

Identifiable::Identifiable(string id) : string(id) {}

Identifiable::Identifiable() : string("_unitialized_") {}

string Identifiable::format(STILConfig& config) const {
    string id = *this;

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
