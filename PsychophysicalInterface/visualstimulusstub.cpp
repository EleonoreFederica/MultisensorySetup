#include "visualstimulusstub.h"
#include "gc.h"

VisualStimulusStub::VisualStimulusStub() : controller_target(""), onset(-99), offset(-99), pixeljson("[]") {
    reset();

}

void VisualStimulusStub::reset()
{
    controller_target="";
    onset=-99;
    offset=-99;
    pixeljson="[]";
}

string VisualStimulusStub::toJSON()
{
    string toreturn = "{";
    toreturn+=GC::qenc("CONTROLLER_TARGET")+": "+GC::qenc(controller_target)+",";
    toreturn+=GC::qenc("ONSET")+": "+to_string(onset)+",";
    toreturn+=GC::qenc("OFFSET")+": "+to_string(offset)+",";
    toreturn+=GC::qenc("PIXELS")+": "+pixeljson;
    toreturn+="}";
    return toreturn;
}

bool VisualStimulusStub::fromJSON(string jsonstring)
{
    reset();
    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)) return false;

    if(doc.HasMember("CONTROLLER_TARGET")) controller_target = doc["CONTROLLER_TARGET"].GetString();
    else return false;
    if(doc.HasMember("ONSET")) onset = doc["ONSET"].GetInt();
    else return false;
    if(doc.HasMember("OFFSET")) offset = doc["OFFSET"].GetInt();
    else return false;
    if(doc.HasMember("PIXELS")) pixeljson = GC::getJSONOfValue(doc["PIXELS"]);
    else return false;
    return true;
}
