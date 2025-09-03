#include "trialstub.h"
#include "gc.h"
#include "document.h"
#include <iostream>

TrialStub::TrialStub() {
    reset();
}

void TrialStub::reset()
{
    name="";
    duration=-99;
    visual_stimuli.clear();
    auditory_stimuli.clear();
}


// La funzione toJSON() crea e restituisce una stringa JSON che rappresenta un oggetto TrialStub.
// this is to create and return a json string representing the whole set of data and cofiguration parameters
// user has just modified or changed. It get all the data type stored, convert into strings and create
// the json
string TrialStub::toJSON()
{
    string toreturn = "{";
    toreturn+=GC::qenc("NAME")+": "+GC::qenc(name)+",";
    toreturn+=GC::qenc("TRIAL_TYPE")+": "+GC::qenc(trial_type)+",";
    toreturn+=GC::qenc("DURATION")+": "+to_string(duration)+",";
    toreturn+="\"VISUAL_STIMULI\": [";
    bool thefirst=true;
    for(auto& v : visual_stimuli){
        if(thefirst)
            thefirst=false;
        else
            toreturn+=",";
        toreturn+=v.toJSON();
    }
    toreturn+="],";
    toreturn+="\"AUDITORY_STIMULI\": [";
    thefirst=true;
    for(auto& a : auditory_stimuli){
        if(thefirst)
            thefirst=false;
        else
            toreturn+=",";
        toreturn+=a.toJSON();
    }
    toreturn+="]";
    toreturn+="}";
    return toreturn;
}


// this is for getting and upload the data contained in a json string to the system whwnever there
// is a change in the configuration made by user. It get a string from json, read and convert it
// into a proper data type (int, string vector<string. etc...)
bool TrialStub::fromJSON(string jsonstring)
{
    reset();

    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)) return false;
    if(doc.HasMember("NAME")) // check if the jsonsting file has a field named "NAME"
        name = doc["NAME"].GetString(); // if yes, then assign its value exctracted by doc[].GetString to the TrialStub variable "name"
    else
        return false;
    if(doc.HasMember("TRIAL_TYPE")) trial_type = doc["TRIAL_TYPE"].GetString();
    if(doc.HasMember("DURATION")) duration = doc["DURATION"].GetInt();
    else return false;
    if(doc.HasMember("VISUAL_STIMULI")){
        for(auto& v : doc["VISUAL_STIMULI"].GetArray()){
            VisualStimulusStub vss;
             vss.fromJSON(GC::getJSONOfValue(v));
            visual_stimuli.push_back(vss);
        }
    }
    if(doc.HasMember("AUDITORY_STIMULI")){
        for(auto& v : doc["AUDITORY_STIMULI"].GetArray()){
            AuditoryStimulusStub vss;
            vss.fromJSON(GC::getJSONOfValue(v));
            auditory_stimuli.push_back(vss);
        }
    }
    return true;
}
