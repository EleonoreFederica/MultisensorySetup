#ifndef AUDITORYSTIMULUSSTUB_H
#define AUDITORYSTIMULUSSTUB_H

#include "gc.h"

class AuditoryStimulusStub
{
public:
    AuditoryStimulusStub();
    AuditoryStimulusStub(const AuditoryStimulusStub& vs) : channel(vs.channel), onset(vs.onset), offset(vs.offset), frequency(vs.frequency), duty_cycle(vs.duty_cycle), cycle_offset(vs.cycle_offset){}

    void reset();

    int channel;
    int onset;
    int offset;
    int frequency;
    float duty_cycle;
    int cycle_offset;

    string toJSON();
    bool fromJSON(string jsonstring);
};

#endif // AUDITORYSTIMULUSSTUB_H
