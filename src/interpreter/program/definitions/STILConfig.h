//
// Created by Gonzalo Solera on 09/08/2017.
//

#ifndef STIL_INTERPRETER_STILCONFIG_H
#define STIL_INTERPRETER_STILCONFIG_H

#include <string>
#include <unordered_map>
#include <istream>
using namespace std;


class STILConfig {

private:

    istream* input;
    class LineNumberStreambuf;
    LineNumberStreambuf* line_buffer;

    void parse_config_file();
    void parse_word_or_comment(string value);
    void parse_word(string& s, string value);

public:
    typedef unordered_map <string, char> EventsMap;
    typedef unordered_map <string, string> NamesMap;

    EventsMap eventsMap;
    NamesMap namesMap;
    bool removeBrackets = false;
    char scan_padding_in;
    char scan_padding_out;

    STILConfig();

    STILConfig(string path);
};


#endif //STIL_INTERPRETER_STILCONFIG_H
