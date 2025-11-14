#ifndef VISUAL_STIMULUS_H
#define VISUAL_STIMULUS_H

#include <vector>
#include <string>
#include "pixel.h"


using namespace std;

class Visual_Stimulus
{
public:
    Visual_Stimulus();
    Visual_Stimulus(string _controller_target,int _onset,int _offset);


    bool fromJSON(string& jsonstring);
    string toJSON();
    void reset();

    string controller_target;
    int onset;
    int offset;
    std::vector<Pixel> pixels;
};


#endif // VISUAL_STIMULUS_H
