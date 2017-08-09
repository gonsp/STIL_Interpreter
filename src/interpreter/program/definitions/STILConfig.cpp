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
    cout << "--------------------------------------" << endl;
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
    assert(s == "event_map");
    input >> s;
    assert(s == "{");
    while(input >> s && s != "}") {
        string stil_event_seq = s;
        char tester_event;
        input >> s;
        assert(s == "->");
        input >> tester_event;
        eventsMap[stil_event_seq] = tester_event;
    }
    assert(s == "}");
}
