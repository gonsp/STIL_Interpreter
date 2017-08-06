//
// Created by Gonzalo Solera on 06/08/2017.
//

#include "WaveForm.h"

WaveForm::WaveForm(string id, char wfc, vector<WaveFormEvent>& events) : Identifiable(id) {
    this->wfc = wfc;
    this->events = events;
}
