#include "trial.h"
#include "gc.h"
#include "document.h"
#include <iostream>

Trial::Trial() : duration(-99) {}

bool Trial::makeCatchTrial()
{
    duration = GC::DEFAULT_TRIAL_DURATION;
    for(auto& g : GC::VISUAL_CONTROLLER_NAMES){  visual_stimuli.push_back(Visual_Stimulus(g,0,0));    }
    return true;
}

// this function extracts values, paramters and arrays of stimuli form the JSON file received from the network inside the "TRIAL"{ } field
bool Trial::fromJSON(string &jsonstring)
{
    reset();

    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)){cout << "ERROR CANNOT PARSE TRIAL FROM JSON " << jsonstring << "\n"; return false;}
    if(doc.HasMember("NAME")) name = doc["NAME"].GetString(); else name="";
    if(doc.HasMember("DURATION")) duration = doc["DURATION"].GetInt();
    else{std::cout << "No Duration in trial, will use default " << to_string(duration) << "\n";}
    if(doc.HasMember("VISUAL_STIMULI")){
        for(auto& v : doc["VISUAL_STIMULI"].GetArray()){
            Visual_Stimulus vs;
            string vjson = GC::getJSONOfValue(v);
            vs.fromJSON(vjson);
            visual_stimuli.push_back(vs);
            inter_stim_interval = duration - vs.offset;
        }
    } else{
        std::cout << "No visual stimuli in trial, will use blanks \n";
        for(auto& g : GC::VISUAL_CONTROLLER_NAMES){  visual_stimuli.push_back(Visual_Stimulus(g,0,0));    }
    }
    if(doc.HasMember("AUDITORY_STIMULI")){
        for(auto& a : doc["AUDITORY_STIMULI"].GetArray()){
            Auditory_Stimulus as;
            string ajson = GC::getJSONOfValue(a);
            as.fromJSON(ajson);
            auditory_stimuli.push_back(as);
            inter_stim_interval = duration - as.offset;
        }
    }
    return true;
}

// this function insert values, paramters and arrays of stimuli to tyhe JSON value of output file created during execution of the experiment
string Trial::toJSON()
{
    string toreturn = "{";
    toreturn+=GC::qenc("NAME")+": "+GC::qenc(name)+",";
    toreturn+=GC::qenc("ISI")+": "+to_string(inter_stim_interval)+",";
    // toreturn+=GC::qenc("ACTIVATION_TIME")+": "+to_string(activation_time)+",";
    // toreturn+=GC::qenc("RECORDED_RESPONSE")+": "+GC::qenc(recorded_response)+",";
    // toreturn+="\"VISUAL_STIMULI\": [";
    // bool thefirst=true;
    // for(auto& v : visual_stimuli){
    //     if(thefirst) thefirst=false; else toreturn+=",";
    //     toreturn+=v.toJSON();
    // }
    // toreturn+="]";
    // if(auditory_stimuli.size()>0){
    //     toreturn+=",\"AUDITORY_STIMULI\": [";
    //     bool thefirst=true;
    //     for(auto& v : auditory_stimuli){
    //         if(thefirst) thefirst=false; else toreturn+=",";
    //         toreturn+=v.toJSON();
    //     }
    //     toreturn+="]";
    // }
    toreturn+="}";
    return toreturn;
}

void Trial::reset()
{
    duration = -99;
    visual_stimuli.clear();
    auditory_stimuli.clear();
}
