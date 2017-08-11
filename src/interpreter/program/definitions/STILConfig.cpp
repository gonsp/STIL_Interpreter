//
// Created by Gonzalo Solera on 09/08/2017.
//

#include "STILConfig.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <sstream>
#include "DefaultConfig.h"


STILConfig::STILConfig() {
    string s((char*) grammar_stil_config);
    istringstream iss(s);
    istream& input(iss);
    parse_input(input);
}

STILConfig::STILConfig(string path) {
    cout << "Parsing config file" << endl;
    ifstream input;
    input.open(path);
    parse_input(input);
    cout << "Parsing correct" << endl;
    cout << "--------------------------------------" << endl;
}

void STILConfig::parse_input(istream& input) {
    string s;

    input >> s;
    check_word(input, s, "event_map");
    input >> s;
    check_word(input, s, "{");
    while(input >> s && s != "}") {
        string stil_event_seq = s;
        char tester_event;
        input >> s;
        assert(s == "->");
        input >> tester_event;
        eventsMap[stil_event_seq] = tester_event;
    }
    assert(s == "}");

    input >> s;
    check_word(input, s, "signal_name_map");
    input >> s;
    check_word(input, s, "{");
    while(input >> s && s != "}") {
        string from = s;
        string to;
        input >> s;
        assert(s == "->");
        getline(input, to);
        if(to.size() > 1 && to[0] == ' ') {
            to = to.substr(1, to.size()-1);
        }
        if(from == "[]" && to == "_") {
            removeBrackets = true;
        } else {
            namesMap[from] = to;
        }
    }
    assert(s == "}");
}

void STILConfig::check_word(istream& input, string& s, string value) {
    if(s.size() >= 2 && s[0] == '/' && s[1] == '/') {
        getline(input, s);
        input >> s;
        check_word(input, s, value);
    } else {
        assert(s == value);
    }
}