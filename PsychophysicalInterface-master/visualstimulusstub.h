#ifndef VISUALSTIMULUSSTUB_H
#define VISUALSTIMULUSSTUB_H

#include <vector>
#include <string>

using namespace std;

class VisualStimulusStub
{
public:
    VisualStimulusStub();
    VisualStimulusStub(const VisualStimulusStub& vs) : controller_target(vs.controller_target), onset(vs.onset), offset(vs.offset), pixeljson(vs.pixeljson){}

    void reset();

    string controller_target;
    int onset;
    int offset;
    string pixeljson;

    string toJSON();
    bool fromJSON(string jsonstring);
};

#endif // VISUALSTIMULUSSTUB_H
