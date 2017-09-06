//
// Created by Gonzalo Solera on 04/09/2017.
//

#ifndef STIL_CONVERTER_STILPATTERNGENERATOR_H
#define STIL_CONVERTER_STILPATTERNGENERATOR_H

#include "../STILState.h"
#include "STILTimingGenerator.h"

using namespace std;

#define PADDING 22

class STILPatternGenerator {

private:
    ofstream output;
    STILProgram* program;

    int* stil_line;
    int padding = PADDING;
    long int prev_last_line_index = 0;
    long int last_line_index = 0;

public:

    STILPatternGenerator() {}

    STILPatternGenerator(string pattern_file, STILProgram* program, int* stil_line);

    void print_headers();

    void clock_cycle(const STILState& state, STILTimingGenerator& timingGenerator);

    void finish();

    void print_tester_inst(string instruction);

    void print_iddq();
};


#endif //STIL_CONVERTER_STILPATTERNGENERATOR_H
