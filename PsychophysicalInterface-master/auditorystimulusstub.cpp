#include "auditorystimulusstub.h"

AuditoryStimulusStub::AuditoryStimulusStub() : channel(-99), onset(-99), offset(-99), frequency(-99.0), duty_cycle(-99.0), cycle_offset(0) {}

void AuditoryStimulusStub::reset()
{
    channel=-99;
    onset=-99;
    offset=-99;
    frequency = -99;
    duty_cycle = -99;
    cycle_offset=-99;
}

string AuditoryStimulusStub::toJSON()
{
    string toreturn = "{";
    toreturn+=GC::qenc("CHANNEL")+": "+to_string(channel)+",";
    toreturn+=GC::qenc("ONSET")+": "+to_string(onset)+",";
    toreturn+=GC::qenc("OFFSET")+": "+to_string(offset)+",";
    toreturn+=GC::qenc("FREQUENCY")+": "+to_string(frequency)+",";
    toreturn+=GC::qenc("DUTY_CYCLE")+": "+to_string(duty_cycle)+",";
    toreturn+=GC::qenc("CYCLE_OFFSET")+": "+to_string(cycle_offset);
    toreturn+="}";
    return toreturn;
}

bool AuditoryStimulusStub::fromJSON(string jsonstring)
{
    reset();
    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)) return false;

    if(doc.HasMember("CHANNEL")) channel = doc["CHANNEL"].GetInt();
    else return false;
    if(doc.HasMember("ONSET")) onset = doc["ONSET"].GetInt();
    else return false;
    if(doc.HasMember("OFFSET")) offset = doc["OFFSET"].GetInt();
    else return false;
    if(doc.HasMember("FREQUENCY")) frequency = doc["FREQUENCY"].GetFloat();
    if(doc.HasMember("DUTY_CYCLE")) duty_cycle = doc["DUTY_CYCLE"].GetFloat();
    if(doc.HasMember("CYCLE_OFFSET")) cycle_offset = doc["CYCLE_OFFSET"].GetInt();
    return true;
}
