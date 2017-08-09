//
// Created by Gonzalo Solera on 09/08/2017.
//

#ifndef STIL_INTERPRETER_STILCONFIG_H
#define STIL_INTERPRETER_STILCONFIG_H

#include <string>
#include <unordered_map>
using namespace std;

class STILConfig {

private:
    void parse_input(istream& input);

public:
    typedef unordered_map <string, char> EventsMap;

    EventsMap eventsMap;

    STILConfig();

    STILConfig(string path);
};


#endif //STIL_INTERPRETER_STILCONFIG_H
