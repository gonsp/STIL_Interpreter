#include <iostream>
#include <STILBaseVisitor.h>

#include "interpreter/STILInterpreter.h"
#include "interpreter/teradyne/STILConfig.h"

using namespace parser;
using namespace antlr4;
using namespace std;

string get_file_name(string file) {
    int i = file.size() - 1;
    while(i >= 0 && file[i] != '.') {
        --i;
    }
    int j = i;
    while(j >= 0 && file[j] != '/') {
        --j;
    }
    return file.substr(j+1, i-j-1);
}

int main(int num_args, char* args[]) {

    if(num_args < 2 || num_args > 7) {
        cerr << "Incorrect number of parameters." << endl;
        cout << "Usage: stil_converter input_file.stil [-v] [-c config_file.config] [-p pattern_exec_name]" << endl;
        cout << "Output: $input_file.atp $input_file.txt" << endl;
        exit(1);
    }

    string file_name = get_file_name(string(args[1]));

    STILConfig config;
    string pattern_exec;

    bool verbose = false;
    for(int i = 2; i < num_args; ++i) {
        string arg(args[i]);
        if(arg == "-c") {
            config = STILConfig(args[i+1]);
            ++i;
        } else if(arg == "-p") {
            pattern_exec = args[i+1];
            ++i;
        } else if(arg == "-v") {
            verbose = true;
        }
    }

    if(!verbose) {
        cout.setstate(ios_base::failbit);
    }

    STILInterpreter interpreter(args[1], "./" + file_name + ".atp", "./" + file_name + ".txt", config);

    if(pattern_exec == "") {
        interpreter.run();
    } else {
        interpreter.run("\"" + pattern_exec + "\"");
    }

    return 0;
}