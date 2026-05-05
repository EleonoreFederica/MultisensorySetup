#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>
#include "trial.h"
#include "responsecontroller.h"
#include "interfaceconnector.h"
#include "auditorycontroller.h"
#include "asio.hpp"

using namespace std;
class Experiment
{
public:
    Experiment();

    enum E_STATE{E_LOAD_CONFIGURATION,E_ORDER_TRIALS,E_RUNNING_TRIAL,E_FINISH_TRIAL,E_END}; //Experimental State
    enum T_STATE{T_STANDBY,T_INFORM_CONTROLLERS,T_TRIAL_ON,T_WAIT_FOR_END,T_END}; //Trial State



    bool fromJSON(string &jsonstring);
    string toJSON();
    void reset();

    string getTrialOutputJSON(Trial& t);

    // Generates a randomized list of N (number_of_loops) trials with modalities (A, V, AV),
    // picking V from visual_stimuli_pool for each V or AV trial.
    void createTrialOrder();

    void runExperiment();
    void switchEState(E_STATE newestate);
    void switchTState(T_STATE newtstate);

    
    bool informControllers(Trial& t);
    bool verifyController(string type,string controllername);
    bool informVisualControllers(Trial& t);
    bool informAudioControllers(Trial& t);


    // string getTestingVisualStimulusString(string controller_target);
    // string createTrialJSON(string controller_target);
    // Restored: genera la stringa HJSON da inviare al controller target per il corretto parsing lato slave
    string messageTrialJSON(std::string controller_target);


    // --- Variabili di configurazione e stato ---
    std::string subjectname = "NULLSUBJECT";
    std::string experimentname = "NULLEXPERIMENT";
    std::string outputfilename = "NULLFILE"; // appends data to this file
    std::string response = "[NULL]";
    int number_of_stimuli;
    int isi_min = 0;
    int isi_max = 0;
    int stim_duration = 0; // durata di ogni singolo stimolo del macro-trial
    int stim_onset = 0;    // onset iniziale del primo stimolo
    int stim_offset = 0;   // offset (può essere usato per logica futura)
    int stim_isi = 0;
    int current_onset = 0;
    int current_offset = 0;
    int current_isi = 0;
    int channel;
    bool writeoutput = true;
    bool use_whitenoise = true; // se true, aggiunge rumore bianco agli stimoli visivi

    E_STATE estate = E_LOAD_CONFIGURATION;
    T_STATE tstate = T_INFORM_CONTROLLERS;

    AuditoryController auditorycontroller;
    ResponseController responsecontroller;
    InterfaceConnector interfaceconnector;
    std::vector<std::string> confirmed_controllers;
    std::vector<std::string> needed_controllers;

    // --- Stimoli e trial ---
    std::vector<Visual_Stimulus> visual_stimuli_pool; // pool di stimoli visivi caricati da file
    std::vector<Trial> trials; // lista dei trial (ora solo uno)
    std::list<int> trialorder; // ordine di esecuzione dei trial (ora solo uno)
    bool loadVisualStimuliPool(const std::string& path = "VisualStimuli/V_STIMULI.json");

private:
    // Variabili per la generazione del macro-trial (blocco unico)
    int stim_index = 0; // indice dello stimolo corrente nel trial
    int visual_index = 0;
    int audio_index = 0;
    std::vector<std::string> modalities = {"A"};
    std::vector<std::string> trial_modalities; // non più usata per loop, ma utile per randomizzazione interna
    std::vector<std::string> block_modalities; // usata per randomizzare l'ordine delle modalità nel blocco
    std::string modality;

    // asio::ip::tcp::socket* socket;
};


#endif // EXPERIMENT_H
