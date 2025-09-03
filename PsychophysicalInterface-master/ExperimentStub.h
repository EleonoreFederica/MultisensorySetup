#ifndef EXPERIMENTSTUB_H
#define EXPERIMENTSTUB_H

#include <string>
#include <vector>
#include "trialstub.h"

using namespace std;

struct ExperimentStub{
    ExperimentStub();
    string subjectname;
    int numberofloops;
    string trialordering;
    bool writeoutput;
    vector<TrialStub> trials;

    string toJSON();
};

#endif // EXPERIMENTSTUB_H
