//
// Created by Gonzalo Solera on 06/08/2017.
//

#ifndef STIL_INTERPRETER_WAVEFORM_H
#define STIL_INTERPRETER_WAVEFORM_H

#include <vector>
#include <iostream>
#include "../../stil/definitions/Identifiable.h"

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
        char event_code;

        WaveFormEvent() {}

        WaveFormEvent(float time, char event_code) {
            this->time = time;
            this->event_code = event_code;
            switch(event_code) {
                case 'D': event = ForceDown; break;
                case 'U': event = ForceUp; break;
                case 'Z': event = ForceOff; break;
                case 'L': event = CompareLow; break;
                case 'H': event = CompareHigh; break;
                case 'X': event = CompareUnknown; break;
                case 'T': event = CompareOff; break;
                case 'N': event = ForceUnknown; break;
                default: cerr << "Unrecognized event: " << event_code << endl; exit(1);
            }
        }
    };

    typedef vector<WaveFormEvent> EventSeq;

    char wfc;
    EventSeq events;

    WaveForm() : Identifiable() {}

    WaveForm(string id, char wfc, vector<WaveFormEvent>& events);

    string event_seq();

};


#endif //STIL_INTERPRETER_WAVEFORM_H
