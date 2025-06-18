#include "trial.h"
#include "gc.h"
#include "document.h"
#include <iostream>

Trial::Trial() {}

bool Trial::makeCatchTrial()
{
    // duration = GC::DEFAULT_TRIAL_DURATION;
    for(auto& g : GC::VISUAL_CONTROLLER_NAMES){
        visual_stimuli.push_back(Visual_Stimulus(g,0,0));
    }
    return true;
}

// !!!!!! ora il trial non viene più generato sulla gui e inviato via network dentro al json, ma viene creato istantaneamente dal master lo stimolo da inviare ad ogni nuovo ciclo a uno slave
// this function extracts values, parameters and arrays of stimuli form the JSON file received from the network inside the "TRIAL"{ } field
bool Trial::fromJSON(string &jsonstring)
{
    reset();

    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)){cout << "ERROR CANNOT PARSE TRIAL FROM JSON " << jsonstring << "\n"; return false;}
    // if(doc.HasMember("NAME")) name = doc["NAME"].GetString(); else name="";
    // else{std::cout << "No Duration in trial, will use default " << to_string(duration) << "\n";}
    if(doc.HasMember("VISUAL_STIMULI")){
        for(auto& v : doc["VISUAL_STIMULI"].GetArray()){
            Visual_Stimulus vs;
            string vjson = GC::getJSONOfValue(v);
            vs.fromJSON(vjson);
            visual_stimuli.push_back(vs);
        }
    } else{
        std::cout << "No visual stimuli in trial, will use blanks \n";
        for(auto& g : GC::VISUAL_CONTROLLER_NAMES){
            visual_stimuli.push_back(Visual_Stimulus(g,0,0));
        }
    }
    if(doc.HasMember("AUDITORY_STIMULI")){
        for(auto& v : doc["AUDITORY_STIMULI"].GetArray()){
            Auditory_Stimulus vs;
            string vjson = GC::getJSONOfValue(v);
            vs.fromJSON(vjson);
            auditory_stimuli.push_back(vs);
        }
    }

    return true;
}

// DA MODIFICARE: in questa funzione dovrebbe poter essere ossibile inserire nel JSON di output la modalita di stimolo corrente e quella precedente
// e inoltre sia l'ISI applicato dipo questo stimolo, che quello precedente
// this function insert values, paramters and arrays of stimuli to the JSON value of output file created during execution of the experiment
string Trial::toJSON()
{
    // Output a JSON array of per-stimulus objects, each with current/previous modality, ISI, and responses
    string toreturn = "[";
    string prev_modality = "NONE";
    int prev_isi = -1;
    bool first = true;
    auto vis_it = visual_stimuli.begin();
    auto aud_it = auditory_stimuli.begin();
    int stim_idx = 0;
    // For each stimulus in the macro-trial, output info
    while (vis_it != visual_stimuli.end() || aud_it != auditory_stimuli.end()) {
        if (!first) toreturn += ",";
        first = false;
        string curr_modality;
        // Determine which stimulus comes next (by onset)
        int vis_onset = (vis_it != visual_stimuli.end()) ? vis_it->onset : INT_MAX;
        int aud_onset = (aud_it != auditory_stimuli.end()) ? aud_it->onset : INT_MAX;
        if (vis_onset <= aud_onset) {
            curr_modality = (aud_onset == vis_onset) ? "AV" : "V";
        } else {
            curr_modality = "A";
        }
        int curr_isi = (vis_onset <= aud_onset && vis_it != visual_stimuli.end()) ? vis_it->isi : (aud_it != auditory_stimuli.end() ? aud_it->isi : -1);
        toreturn += "{ ";
        toreturn += GC::qenc("STIMULUS_INDEX") + ": " + to_string(stim_idx) + ", ";
        toreturn += GC::qenc("MODALITY") + ": " + GC::qenc(curr_modality) + ", ";
        toreturn += GC::qenc("PREV_MODALITY") + ": " + GC::qenc(prev_modality) + ", ";
        toreturn += GC::qenc("ISI") + ": " + to_string(curr_isi) + ", ";
        toreturn += GC::qenc("PREV_ISI") + ": " + to_string(prev_isi) + ", ";
        // NON scrivere i campi VISUAL e AUDITORY
        toreturn += GC::qenc("RESPONSES") + ": [] "; // responses are handled in experiment output
        toreturn += "}";
        // Advance iterators
        if (vis_onset <= aud_onset && vis_it != visual_stimuli.end()) ++vis_it;
        if (aud_onset <= vis_onset && aud_it != auditory_stimuli.end()) ++aud_it;
        prev_modality = curr_modality;
        prev_isi = curr_isi;
        ++stim_idx;
    }
    toreturn += "]";
    return toreturn;
}

void Trial::reset()
{
    // duration = -99;
    visual_stimuli.clear();
    auditory_stimuli.clear();
}
