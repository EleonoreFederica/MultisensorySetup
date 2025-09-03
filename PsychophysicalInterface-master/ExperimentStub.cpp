#include "ExperimentStub.h"
#include "gc.h"

ExperimentStub::ExperimentStub(){}

string ExperimentStub::toJSON()
{
    string toreturn="{";
    toreturn+=GC::qenc("SUBJECTNAME")+": "+GC::qenc(subjectname)+",";
    toreturn+=GC::qenc("NUMBER_OF_LOOPS")+": "+to_string(numberofloops)+",";
    toreturn+=GC::qenc("TRIALORDERING")+": "+GC::qenc(trialordering)+",";
    toreturn+=GC::qenc("WRITEOUTPUT")+": "+(writeoutput ? "true" : "false")+",";
    toreturn+=GC::qenc("TRIALS")+": [";
    bool thefirst=true;
    for(auto& t : trials){
        if(thefirst) thefirst=false; else toreturn+=",";
        toreturn+=t.toJSON();
    }
    toreturn+="]";
    toreturn+="}";
    return toreturn;
}

