#ifndef AUDITORY_STIMULUS_H
#define AUDITORY_STIMULUS_H

#include "gc.h"

class Auditory_Stimulus
{
public:
    enum STATE{PRE,DURING,POST};
    Auditory_Stimulus();

    Auditory_Stimulus(int _channel,int _onset,int _offset,float _frequency,float _duty_cycle,int _cycle_offset);


    bool fromJSON(string& jsonstring);
    string toJSON();
    void reset();

    int channel;
    int onset;
    int offset;
    float frequency;
    float duty_cycle;
    int cycle_offset;
    int isi;
    STATE state=PRE;

};

#endif // AUDITORY_STIMULUS_H
