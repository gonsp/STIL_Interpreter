//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "SignalState.h"
#include "iostream"

using namespace std;

SignalState::SignalState(STILProgram* program) {
    this->program = program;
    next_vector = vector<char>(program->signals.size(), ' ');
}

void SignalState::clock_cicle(ostream& output) {
    output << " > " << waveform_table << " ";
    for(int i = 0; i < next_vector.size(); ++i) {
        output << next_vector[i] << " ";
    }
    output << ";" << endl;
}
