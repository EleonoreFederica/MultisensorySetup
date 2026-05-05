#ifndef TRIAL_H
#define TRIAL_H

#include <vector>
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
    int total_duration;
    int onset;
    int offset;
    int isi_min;
    int isi_max;
    // long activation_time;           //overwritten when trial is run
    // string recorded_response;       //overwritten when trial is run
    std::vector<Visual_Stimulus> visual_stimuli;
    std::vector<Auditory_Stimulus> auditory_stimuli;
};



#endif // TRIAL_H
