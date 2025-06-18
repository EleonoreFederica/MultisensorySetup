#include "visual_stimulus.h"
#include <iostream>
#include "gc.h"

Visual_Stimulus::Visual_Stimulus() : controller_target("NULL"), onset(-99), offset(-99) {}

Visual_Stimulus::Visual_Stimulus(string _controller_target, int _onset, int _offset) : controller_target(_controller_target), onset(_onset), offset(_offset)
{

}

// this function extracts values, parameters and arrays of stimuli from the JSON file uploaded form JSON stored in the path
bool Visual_Stimulus::fromJSON(string &jsonstring)
{
    reset();

    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)) {std::cout << "ERROR PARSING VISUAL STIMULUS\n"; return false;}
    if(doc.HasMember("CONTROLLER_TARGET")) controller_target = doc["CONTROLLER_TARGET"].GetString();
    else {std::cout << "VISUAL STIMULI MUST SPECIFY CONTROLLER TARGET"; return false;}
    if(doc.HasMember("POSITION")) position = doc["POSITION"].GetInt();
    if(doc.HasMember("PIXELS")){
        for(auto& p : doc["PIXELS"].GetArray()){
            pixels.push_back(Pixel(p.GetArray()[0].GetInt(),p.GetArray()[1].GetInt(),p.GetArray()[2].GetInt(),p.GetArray()[3].GetInt(),p.GetArray()[4].GetInt()));
        }
    }
    return true;
}

// this function insert values, parameters and arrays of stimuli to the JSON to be sent to the controller
// in the form json: { "ONSET": <value>, "OFFSET": <value>, "ISI": <value>, "PIXELS": [{x,y,r,g,b},{x,y,r,g,b},...]}
string Visual_Stimulus::toJSON() const
{
    string toreturn;
    toreturn += GC::qenc("ONSET") + ": " + to_string(onset) + ",";
    toreturn += GC::qenc("OFFSET") + ": " + to_string(offset) + ",";
    toreturn += GC::qenc("ISI") + ": " + to_string(isi) + ",";
    toreturn += GC::qenc("PIXELS") + ": [";
    bool thefirst = true;
    for(auto& p : pixels){
        if(thefirst) thefirst = false; else toreturn += ",";
        toreturn += p.toJSON();
    }
    toreturn += "]";
    return toreturn;
}

void Visual_Stimulus::reset()
{
    controller_target="NULL";
    onset=-99;
    offset=-99;
    pixels.clear();
}


