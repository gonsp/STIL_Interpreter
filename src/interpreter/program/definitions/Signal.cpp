//
// Created by Gonzalo Solera on 03/08/2017.
//

#include "Signal.h"

Signal::Signal(string id, signal_dir dir) : Identifiable(id) {
    this->dir = dir;
}