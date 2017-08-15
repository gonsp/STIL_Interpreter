//
// Created by Gonzalo Solera on 15/08/2017.
//

#ifndef STIL_CONVERTER_STILFILEPREPROCESSOR_H
#define STIL_CONVERTER_STILFILEPREPROCESSOR_H

#include <string>
#include <fstream>
using namespace std;

class STILFilePreprocessor {

private:

    ifstream original;
    ofstream processed;

    string file_path;

public:

    STILFilePreprocessor(string file_path);

    void remove_user_keyword_definitions();
};


#endif //STIL_CONVERTER_STILFILEPREPROCESSOR_H
