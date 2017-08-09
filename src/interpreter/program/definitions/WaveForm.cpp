//
// Created by Gonzalo Solera on 06/08/2017.
//

#include "WaveForm.h"

WaveForm::WaveForm(string id, char wfc, vector<WaveFormEvent>& events) : Identifiable(id) {
    this->wfc = wfc;
    this->events = events;
}

string WaveForm::event_seq() {
    string event_seq(events.size(), ' ');
    for(int i = 0; i < events.size(); ++i) {
        event_seq[i] = events[i].event_code;
    }
    return event_seq;
}
