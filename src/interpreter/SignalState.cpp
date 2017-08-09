//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "SignalState.h"
#include "iostream"

using namespace std;

SignalState::SignalState(STILProgram* program) {
    this->program = program;
    next_vector = program->signals;
}

void SignalState::execute_assigs(list<Assig> assigs) {
    for(auto it = assigs.begin(); it != assigs.end(); ++it) {
        cout << it->first << " = " << it->second << endl;
    }
}

void SignalState::clock_cycle(ostream& output) {
    output << " > " << waveform_table << " ";
    for(auto it = next_vector.begin(); it != next_vector.end(); ++it) {
        output << it->second.value << " ";
    }
    output << ";" << endl;
}
