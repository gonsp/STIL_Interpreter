#include <iostream>
#include <STILBaseVisitor.h>

#include "interpreter/STILInterpreter.h"

using namespace parser;
using namespace antlr4;
using namespace std;

string get_file_name(string file) {
    int i = file.size() - 1;
    while(i >= 0 && file[i] != '.') {
        --i;
    }
    return file.substr(0, i);
}

int main(int num_args, char* args[]) {

    if(num_args != 2 && num_args != 3) {
        cerr << "Incorrect number of parameters." << endl;
        cout << "Usage: stil_converter input_file.stil [pattern_exec_name]" << endl;
        cout << "Output: $input_file.atp $input_file.txt" << endl;
        exit(1);
    }

    string path = string(args[1]);
    path = get_file_name(path);

    STILInterpreter interpreter(args[1], path + ".atp", path + ".txt");

    if(num_args == 2) {
        interpreter.run();
    } else {
        string pattern_exec(args[2]);
        interpreter.run("\"" + pattern_exec + "\"");
    }

    return 0;
}