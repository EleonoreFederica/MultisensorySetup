#ifndef TRIALSTUB_H
#define TRIALSTUB_H

#include <list>
#include "visualstimulusstub.h"
#include "auditorystimulusstub.h"

using namespace std;

class TrialStub
{
public:
    TrialStub();

    void reset();


    string name;
    string trial_type;
    int duration;
    list<VisualStimulusStub> visual_stimuli;
    list<AuditoryStimulusStub> auditory_stimuli;
    string toJSON();
    bool fromJSON(string jsonstring);
};

#endif // TRIALSTUB_H
