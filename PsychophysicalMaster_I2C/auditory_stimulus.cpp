#include "auditory_stimulus.h"
#include <iostream>

Auditory_Stimulus::Auditory_Stimulus() {
    reset();
}

Auditory_Stimulus::Auditory_Stimulus(uint8_t _channel, uint16_t _onset, uint16_t _offset, float _frequency, float _duty_cycle, int _cycle_offset) : channel(_channel), onset(_onset), offset(_offset), frequency(_frequency), duty_cycle(_duty_cycle), cycle_offset(_cycle_offset)
{

}

bool Auditory_Stimulus::fromJSON(string &jsonstring)
{
    reset();

    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)) {std::cout << "ERROR PARSING AUDITORY STIMULUS\n"; return false;}
    if(doc.HasMember("CHANNEL")) channel = doc["CHANNEL"].GetInt();
    else {std::cout << "AUDITORY STIMULI MUST SPECIFY CHANNEL TARGET"; return false;}
    if(doc.HasMember("ONSET")) onset = doc["ONSET"].GetInt();
    if(doc.HasMember("OFFSET")) offset = doc["OFFSET"].GetInt();
    if(doc.HasMember("FREQUENCY")) frequency = doc["FREQUENCY"].GetFloat();
    if(doc.HasMember("DUTY_CYCLE")) duty_cycle = doc["DUTY_CYCLE"].GetFloat();
    if(doc.HasMember("CYCLE_OFFSET")) cycle_offset = doc["CYCLE_OFFSET"].GetInt();
    return true;
}

string Auditory_Stimulus::toJSON()
{
    string toreturn;
    toreturn+=GC::qenc("C")+": "+to_string(channel)+",";
    toreturn+=GC::qenc("ON")+": "+to_string(onset)+",";
    toreturn+=GC::qenc("OFF")+": "+to_string(offset);
    // toreturn+=GC::qenc("FREQUENCY")+": "+to_string(frequency)+",";
    // toreturn+=GC::qenc("DUTY_CYCLE")+": "+to_string(duty_cycle)+",";
    // toreturn+=GC::qenc("CYCLE_OFFSET")+": "+to_string(cycle_offset);
    return toreturn;
}

void Auditory_Stimulus::reset()
{
    channel=-99;
    onset=-99;
    offset=-99;
    frequency=-99.0;
    duty_cycle=-99.0;
    cycle_offset=-99;

    state=PRE;
}
