//
// Created by Gonzalo Solera on 06/08/2017.
//

#ifndef STIL_INTERPRETER_WAVEFORM_H
#define STIL_INTERPRETER_WAVEFORM_H

#include <vector>
#include "Identifiable.h"

using namespace std;

class WaveForm : public Identifiable {

public:

    struct WaveFormEvent {

        enum Event {
            ForceDown, ForceUp, ForceOff, CompareLow, CompareHigh,
            CompareUnknown, CompareOff, ForceUnknown
        };

        float time;
        Event event;

        WaveFormEvent() {}

        WaveFormEvent(float time, Event event) {
            this->time = time;
            this->event = event;
        }
    };

    char wfc;
    vector<WaveFormEvent> events;

    WaveForm() : Identifiable() {}

    WaveForm(string id, char wfc, vector<WaveFormEvent>& events);

};


#endif //STIL_INTERPRETER_WAVEFORM_H
