//
// Created by Gonzalo Solera on 04/08/2017.
//

#include "WaveFormTable.h"

WaveFormTable::WaveFormTable(string id, float period, WaveForms& waveforms) : Identifiable(id) {
    this->period = period;
    this->waveforms = waveforms;
}
