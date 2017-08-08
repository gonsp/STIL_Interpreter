//
// Created by Gonzalo Solera on 08/08/2017.
//

#include "SignalState.h"

SignalState::SignalState(int size) {
    next_vector = vector<char>(size, ' ');
}
