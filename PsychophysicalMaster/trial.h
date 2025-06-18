#ifndef TRIAL_H
#define TRIAL_H

#include <list>
#include "visual_stimulus.h"
#include "auditory_stimulus.h"

using namespace std;
class Trial
{
public:
    Trial();

    bool makeCatchTrial();

    bool fromJSON(string& jsonstring);
    string toJSON();


    void reset();

    string name;
    int duration;
    int inter_stim_interval;
    // long activation_time;           //overwritten when trial is run
    // string recorded_response;       //overwritten when trial is run
    list<Visual_Stimulus> visual_stimuli;
    list<Auditory_Stimulus> auditory_stimuli;
};



#endif // TRIAL_H
