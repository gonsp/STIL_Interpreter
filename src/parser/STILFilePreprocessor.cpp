//
// Created by Gonzalo Solera on 15/08/2017.
//

#include <iostream>
#include <sstream>
#include <unordered_set>
#include "STILFilePreprocessor.h"

STILFilePreprocessor::STILFilePreprocessor(string file_path) {
    this->file_path = file_path;
    original.open(file_path);
    processed.open(file_path+".tmp");
}

// The arbitrary structure of a user_keyword block makes impossible
// (or really difficult) the parsing of the stil file.
// This workaround consists on a pre-processor of the input file
// to remove the definitions of the user_keywords by filtering the
// input file into a temporal one. Then deleting the original and
// changing the temporal name to the original one.
void STILFilePreprocessor::remove_user_keyword_definitions() {
    cout << "Pre-processing input file (removing user keywords)" << endl;
    unordered_set<string> keywords;
    string line;
    while(!original.eof()) {
        getline(original, line);
        istringstream iss(line);
        string s;
        iss >> s;
        if(s == "UserKeywords") {
            while(iss >> s) {
                if(s.back() == ';') {
                    s.pop_back();
                }
                if(s.size() > 0) {
                    keywords.insert(s);
                }
            }
        } else if(keywords.count(s) != 0) {
            if(line.back() == '{') { // It's a definition, not a use
                cout << "Removing user keyword definition: " << s << endl;
                int open_brackets = 1;
                while(open_brackets > 0) {
                    char c;
                    original >> c;
                    if(c == '{') {
                        ++open_brackets;
                    } else if(c == '}') {
                        --open_brackets;
                    }
                }
            }
        } else {
            processed << line << endl;
        }
    }
    original.close();
    processed.close();
    string tmp_path = file_path + ".tmp";
    remove(file_path.c_str());
    rename(tmp_path.c_str(), file_path.c_str());
}
