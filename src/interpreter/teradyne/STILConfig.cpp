//
// Created by Gonzalo Solera on 09/08/2017.
//

#include "STILConfig.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "definitions/DefaultConfig.h"

class STILConfig::LineNumberStreambuf : public std::streambuf {

private:
    std::streambuf* mySource;
    std::istream* myOwner;
    bool myIsAtStartOfLine;
    char myBuffer;

protected:
    int underflow() {
        int ch = mySource->sbumpc();
        if(ch != EOF) {
            myBuffer = ch;
            setg(&myBuffer, &myBuffer, &myBuffer + 1);
            if(myIsAtStartOfLine) {
                ++myLineNumber;
            }
            myIsAtStartOfLine = myBuffer == '\n';
        }
        return ch;
    }

public:
    int myLineNumber;

    LineNumberStreambuf(std::istream& owner) : mySource(owner.rdbuf()), myOwner(&owner), myIsAtStartOfLine(true), myLineNumber(0) {
        myOwner->rdbuf(this);
    }
};


STILConfig::STILConfig() {
    string s((char*) grammar_stil_config);
    istringstream iss(s);
    input = &iss;
    parse_config_file();
    input = NULL;
}

STILConfig::STILConfig(string path) {
    cout << "Parsing config file" << endl;
    ifstream file;
    file.open(path);
    input = &file;
    parse_config_file();
    input = NULL;
    cout << "Config file parsed correctly" << endl;
    cout << "--------------------------------------" << endl;
}

void STILConfig::parse_config_file() {

    if(input == NULL) {
        cerr << "Input stream to parser the config file is null" << endl;
        exit(1);
    }

    istream& input = *(this->input);
    LineNumberStreambuf line_buffer(input);
    this->line_buffer = &line_buffer;

    string s;

    // EVENT MAP
    parse_word_or_comment("event_map");
    parse_word_or_comment("{");
    while(input >> s && s != "}") {
        string stil_event_seq = s;
        char tester_event;
        string translations;

        input >> s;
        parse_word(s, "->");
        input >> tester_event;
        getline(input, translations);

        list<WaveTranslation> wave_translations;
        istringstream iss(translations);
        char c;
        while(iss >> c) {   // It's a "coma"
            iss >> c;       // It's a left parenthesis
            string rule;    // It's a full rule
            getline(iss, rule, ')');
            wave_translations.push_back(WaveTranslation(rule));
        }

        eventsMap[stil_event_seq] = EventsTranslation(tester_event, wave_translations);
    }
    parse_word(s, "}");

    // SIGNAL NAME MAP
    parse_word_or_comment("signal_name_map");
    parse_word_or_comment("{");
    while(input >> s && s != "}") {
        string from = s;
        string to;

        input >> s;
        parse_word(s, "->");
        getline(input, to);
        if(to.size() > 1 && to[0] == ' ') {
            to = to.substr(1, to.size() - 1);
        }
        if(from == "[]" && to == "_") {
            removeBrackets = true;
        } else {
            namesMap[from] = to;
        }
    }
    parse_word(s, "}");

    // SCAN PADDING
    parse_word_or_comment("scan_padding");
    parse_word_or_comment("{");
    input >> s;
    parse_word(s, "scan_in");
    input >> s;
    parse_word(s, "->");
    input >> scan_padding_in;
    input >> s;
    parse_word(s, "scan_out");
    input >> s;
    parse_word(s, "->");
    input >> scan_padding_out;
    input >> s;
    parse_word(s, "}");

    // IDDQ ACTION
    parse_word_or_comment("iddq_action");
    parse_word_or_comment("{");
    getline(input, s);
    getline(input, iddq_action, '}');
}

void STILConfig::parse_word_or_comment(string value) {
    string s;
    *input >> s;
    if(s.size() >= 2 && s[0] == '/' && s[1] == '/') {
        getline(*input, s);
        parse_word_or_comment(value);
    } else {
        parse_word(s, value);
    }
}

void STILConfig::parse_word(string& s, string value) {
    if(s != value) {
        cerr << "Error parsing config file at line " << line_buffer->myLineNumber << endl;
        cerr << "Expecting: \"" << value << "\" but read: \"" << s << "\"" << endl;
        exit(1);
    }
}