//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "SignalState.h"
#include "iostream"

using namespace std;

SignalState::SignalState(int size) {
    next_vector = vector<char>(size, ' ');
}

void SignalState::clock_cicle(ostream& output) {
    for(int i = 0; i < next_vector.size(); ++i) {
        output << next_vector[i] << " ";
    }
    output << ";" << endl;
}
