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

void SignalState::clock_cicle(ostream& output) {
    output << " > " << waveform_table << " ";
    for(auto it = next_vector.begin(); it != next_vector.end(); ++it) {
        output << it->second.value << " ";
    }
    output << ";" << endl;
}
