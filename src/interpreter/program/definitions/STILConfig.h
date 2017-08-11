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
    void check_word(istream& input, string& s, string value);

public:
    typedef unordered_map <string, char> EventsMap;
    typedef unordered_map <string, string> NamesMap;

    EventsMap eventsMap;
    NamesMap namesMap;
    bool removeBrackets = false;

    STILConfig();

    STILConfig(string path);
};


#endif //STIL_INTERPRETER_STILCONFIG_H
