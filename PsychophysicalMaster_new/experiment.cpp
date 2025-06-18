#include "experiment.h"
#include "gc.h"
#include <iostream>
#include "asio.hpp"
#include "stdio.h"
#include <libevdev-1.0/libevdev/libevdev.h>
#include <fstream>
#include <random>
#include <algorithm>


using namespace std;
using asio::ip::tcp;

Experiment::Experiment() {}

// DA CAMBIARE: il json inviato dall'interfaccia avrà campi diversi cone num stimoli per trial, ISI min, ISI max, nome soggetto, posizione spaziale matrici coinvolte
bool Experiment::fromJSON(string& jsonstring)
{

    rapidjson::Document doc;

    cout << "\rLoading experiment from json...";

    if(!GC::loadJSONFromString(doc,jsonstring)){cout << "ERROR LOADING EXPERIMENT\n"; return false;}
    if(doc.HasMember("SUBJECTNAME")) subjectname = doc["SUBJECTNAME"].GetString();
    if(doc.HasMember("NUMBER_OF_STIMULI")) number_of_stimuli = doc["NUMBER_OF_STIMULI"].GetInt();
    if(doc.HasMember("STIM_DURATION")) stim_duration = doc["STIM_DURATION"].GetInt();
    if(doc.HasMember("STIM_ONSET")) stim_onset = doc["STIM_ONSET"].GetInt();
    else stim_onset = 0;
    if(doc.HasMember("STIM_OFFSET")) stim_offset = doc["STIM_OFFSET"].GetInt();
    else stim_offset = 0;
    if(doc.HasMember("ISI_MIN")) isi_min = doc["ISI_MIN"].GetInt();
    if(doc.HasMember("ISI_MAX")) isi_max = doc["ISI_MAX"].GetInt();
    if(doc.HasMember("WRITEOUTPUT")) writeoutput = doc["WRITEOUTPUT"].GetBool();
    if(doc.HasMember("USE_WHITENOISE")) use_whitenoise = doc["USE_WHITENOISE"].GetBool();

    cout << "loaded header...\n ";

    // TRIALORDERING is deprecated and no longer loaded from JSON
    // if(doc.HasMember("TRIALORDERING")) { /* removed: legacy ordering logic */ }
    return true;
}

void Experiment::reset()
{
    estate=E_LOAD_CONFIGURATION;
    tstate=T_STANDBY;
}

// DA CAMBIARE: il json di output deve salvare modalità distimolo i-esima, RT i-esima, modalità di stmolo i-1 esima, ISI fra i-1 e i esima
string Experiment::getTrialOutputJSON(Trial &t)
{
    string toreturn ="{";
    toreturn+="     "+GC::qenc("SUBJECTNAME") + ": " + GC::qenc(subjectname) + ",";
    toreturn+="     "+GC::qenc("TIMESTAMP") + ": " + GC::getTimeStamp() + ",";
    // Instead of a single responses array, output per-stimulus responses in the TRIAL array
    toreturn+="     "+GC::qenc("TRIAL") + ": "+ t.toJSON();
    toreturn+="}";
    return toreturn;
}

// Carica tutti gli stimoli visivi da un file JSON (V_STIMULI.json) e li inserisce nel pool visual_stimuli_pool.
// Restituisce true se il caricamento ha successo, false in caso di errore di apertura o parsing.
bool Experiment::loadVisualStimuliPool(const string& path) {
    visual_stimuli_pool.clear();
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr << "ERROR: Cannot open visual stimuli file: " << path << std::endl;
        return false;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    string jsonstring = buffer.str();
    rapidjson::Document doc;
    if (!GC::loadJSONFromString(doc, jsonstring)) {
        std::cerr << "ERROR: Cannot parse visual stimuli JSON." << std::endl;
        return false;
    }
    if (!doc.IsArray()) {
        std::cerr << "ERROR: Visual stimuli JSON is not an array." << std::endl;
        return false;
    }
    for (auto& v : doc.GetArray()) {
        string vjson = GC::getJSONOfValue(v);
        Visual_Stimulus vs;
        if (vs.fromJSON(vjson)) {
            visual_stimuli_pool.push_back(vs);
        } else {
            std::cerr << "WARNING: Skipped invalid visual stimulus entry." << std::endl;
        }
    }
    std::cout << "Loaded " << visual_stimuli_pool.size() << " visual stimuli from pool." << std::endl;
    return true;
}

void Experiment::createTrialOrder() {
    trials.clear();
    trialorder.clear();
    trial_modalities.clear();

    // Random engine seeded with random_device for true randomness
    std::random_device rd;
    std::mt19937 rng(rd());

    // 1. Randomizza la sequenza delle modalità per il blocco
    block_modalities = modalities;
    std::shuffle(block_modalities.begin(), block_modalities.end(), rng);

    // 2. Prepara la lista randomizzata delle modalità per tutti i trial
    std::vector<std::string> trial_mods;
    for (int i = 0; i < number_of_stimuli; ++i) {
        trial_mods.push_back(block_modalities[i % block_modalities.size()]);
    }
    std::shuffle(trial_mods.begin(), trial_mods.end(), rng);
    // trial_mods è il vettore che contien la lista randomizzata di stringhe "A", "V" o "AV" per N elementi totali

    // 3. Prepara una copia randomizzata del pool di stimoli visivi
    std::vector<Visual_Stimulus> visual_pool = visual_stimuli_pool;
    std::shuffle(visual_pool.begin(), visual_pool.end(), rng);

    // 4. Prepara una copia randomizzata dei canali audio disponibili
    std::vector<int> audio_ports = GC::AUDIO_PORTS;
    std::shuffle(audio_ports.begin(), audio_ports.end(), rng);

    Trial t;
    t.name = "MACRO_TRIAL";
    t.visual_stimuli.clear();
    t.auditory_stimuli.clear();

    int onset = stim_onset;
    size_t visual_idx = 0;
    size_t audio_idx = 0;

    int isi;

    for (int i = 0; i < number_of_stimuli; ++i) {
        const std::string& mod = trial_mods[i]; // col ciclo scorre tutte le modalità in ordine insertite in lista trial_mods e per cacuna in base al tipo crea gli stimolicorrispondenti
        trial_modalities.push_back(mod);
        std::uniform_int_distribution<int> isi_dist(isi_min, isi_max);
        isi = (isi_max > isi_min) ? isi_dist(rng) : isi_min;
        // cout << "[DEBUG] ISI[" << i << "]: " << isi << endl;
        if (mod == "A") {
            Auditory_Stimulus astim;
            astim.onset = onset;
            astim.offset = onset + stim_duration;
            astim.state = Auditory_Stimulus::PRE;
            astim.isi = isi;
            // Randomizza il canale audio per ogni stimolo
            if (!audio_ports.empty()) {
                if (audio_idx >= audio_ports.size()) {
                    std::shuffle(audio_ports.begin(), audio_ports.end(), rng);
                    audio_idx = 0;
                }
                astim.channel = audio_ports[audio_idx++];
            } else {
                astim.channel = 0;
            }
            astim.frequency = 5000.0f;
            astim.duty_cycle = 50.0f;
            astim.cycle_offset = 0;
            t.auditory_stimuli.push_back(astim);
        } else if (mod == "V") {
            if (!visual_pool.empty()) {
                if (visual_idx >= visual_pool.size()) {
                    std::shuffle(visual_pool.begin(), visual_pool.end(), rng);
                    visual_idx = 0;
                }
                Visual_Stimulus vstim = visual_pool[visual_idx++];
                vstim.onset = onset;
                vstim.offset = onset + stim_duration;
                vstim.isi = isi;
                t.visual_stimuli.push_back(vstim);
            }
        } else if (mod == "AV") {
            // Stimolo visivo
            if (!visual_pool.empty()) {
                if (visual_idx >= visual_pool.size()) {
                    std::shuffle(visual_pool.begin(), visual_pool.end(), rng);
                    visual_idx = 0;
                }
                Visual_Stimulus vstim = visual_pool[visual_idx++];
                vstim.onset = onset;
                vstim.offset = onset + stim_duration;
                vstim.isi = isi;
                t.visual_stimuli.push_back(vstim);
            }
            // Stimolo acustico
            Auditory_Stimulus astim;
            astim.onset = onset;
            astim.offset = onset + stim_duration;
            astim.state = Auditory_Stimulus::DURING;
            astim.isi = isi;
            if (!audio_ports.empty()) {
                if (audio_idx >= audio_ports.size()) {
                    std::shuffle(audio_ports.begin(), audio_ports.end(), rng);
                    audio_idx = 0;
                }
                astim.channel = audio_ports[audio_idx++];
            } else {
                astim.channel = 0;
            }
            astim.frequency = 5000.0f;
            astim.duty_cycle = 50.0f;
            astim.cycle_offset = 0;
            t.auditory_stimuli.push_back(astim);
        }
        onset += stim_duration + isi;

    }
    t.total_duration = onset + stim_duration + isi;
    std::cout << "\r[DEBUG] Total duration: " << t.total_duration << std::endl;
    // Shuffle finale delle liste di stimoli per ulteriore randomizzazione
    // if (!t.visual_stimuli.empty()) {
    //     std::shuffle(t.visual_stimuli.begin(), t.visual_stimuli.end(), rng);
    // }
    // if (!t.auditory_stimuli.empty()) {
    //     std::shuffle(t.auditory_stimuli.begin(), t.auditory_stimuli.end(), rng);
    // }

    trials.push_back(t);
    trialorder.push_back(0);
}

void Experiment::runExperiment()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto start_trial = std::chrono::high_resolution_clock::now();
    auto this_time = std::chrono::high_resolution_clock::now();
    bool thefirsttrial=true;
    // bool firstauditory=true;
    confirmed_controllers.clear();

    while(estate!=E_END){
        // Caricamento della configurazione sperimentale
        // In questo stato il sistema carica i parametri dell'esperimento da file o da interfaccia TCP,
        // inizializza le variabili globali e prepara il pool di stimoli visivi.
        if(estate==E_LOAD_CONFIGURATION){
            GC::INT_EXECUTION = false;
            lgGpioWrite(GC::GPIO,GC::TRIAL_RESET_PORT,0);
            if (thefirsttrial){
                lgGpioWrite(GC::GPIO,GC::RESPONSE_INTERRUPT_PORT,0);
            }
            cout << "\rE: Load configuration\n";

            string experimentjson="{}";
            // case: use the Interface configuration transmission (default)
            if(GC::USE_INTERFACE_NOT_FILE){
                if(interfaceconnector.waitForInterfaceConnection()==InterfaceConnector::SUCCESS){
                    experimentjson = interfaceconnector.experimentJSON;
                    cout << "received experimentjson " << experimentjson << "\n";
                }
            }
            // case: not use the Interace but directly the sample_experiment
            else experimentjson = GC::getJSONStringFromFile(GC::EXPERIMENT_FILE_IF_USED);
            if(experimentjson!="{}"){
                cout << "\rLoading json for experiment...";
                fromJSON(experimentjson);
                // Carica il pool di stimoli visivi dopo il parsing dei parametri
                if (!loadVisualStimuliPool(GC::V_STIMULI_PATH)) {
                    std::cerr << "\nERROR: Visual stimuli pool not loaded!" << std::endl;
                }
                cout << "done!\n";
                thefirsttrial=true;
                string timestamp = GC::getTimeStamp();
                string experimentfilename = timestamp+"experiment.json";
                // GC::appendToFile(experimentfilename,experimentjson);
                outputfilename = timestamp+subjectname+".json";
                if(writeoutput) GC::appendToFile(outputfilename,"[");
                cout << "Done loading successfully. Switching to trial ordering...\n";
                switchEState(E_ORDER_TRIALS);
            }
        }

        // Generazione e ordinamento dei trial
        // In questo stato il sistema genera la sequenza randomizzata di stimoli (macro-trial),
        // popola i vettori trials e trialorder, e prepara l'esecuzione sperimentale.
        else if(estate==E_ORDER_TRIALS){
            thefirsttrial=true;
            cout << "\rE: Create trial order\n";
            createTrialOrder();
            // Print numer of stimuli for each modality
            int nA = 0, nV = 0, nAV = 0;
            for(const auto& m : trial_modalities){
                if(m == "A") ++nA;
                else if(m == "V") ++nV;
                else ++nAV;
            }
            cout << "\rTRIALS PER MODALITY: A=" << nA << "| V=" << nV << "| AV=" << nAV << "\n";
            // stim_index = 0; // Inizializza l'indice degli stimoli solo all'inizio di un nuovo macro-trial
            // visual_index = 0;
            // audio_index = 0;
            if(trialorder.size()>0){

                switchEState(E_RUNNING_TRIAL);
                switchTState(T_STANDBY);
            }
            else {cout << "ERROR: trialorder is empty after ordering\n"; switchEState(E_END);}
        }

        // Esecuzione del trial corrente
        // In questo stato il sistema gestisce la presentazione degli stimoli, la comunicazione con i controller slave,START
        // la raccolta delle risposte e la temporizzazione degli eventi per il trial corrente.
        else if(estate==E_RUNNING_TRIAL){
            // Attesa di avvio trial
            // In questo stato il sistema attende che il soggetto sia pronto (pedale o altro trigger),
            // prepara la lista dei controller necessari e segnala la disponibilità di un nuovo trial.
            if(tstate==T_STANDBY){
                lgGpioWrite(GC::GPIO,GC::TRIAL_RESET_PORT,1); // inform the slave a new trial is available
                if((GC::USE_PEDAL_CONTROL) && (responsecontroller.getPedalState())){ // check a pression of the pedal
                    lgGpioWrite(GC::GPIO,GC::SBJ_READY_PORT,1); // if pedal pressed, tell the slave to interrupt the WAIT_SBJ_READY state
                    confirmed_controllers.clear(); // list of the controllers that have confirmed the conection
                    needed_controllers.clear(); // list of the controllers needed for this specific trial
                    for(auto& p : trials[trialorder.front()].visual_stimuli){
                        needed_controllers.push_back(p.controller_target);
                    }
                    switchTState(T_INFORM_CONTROLLERS);
                } else if (!GC::USE_PEDAL_CONTROL){
                    lgGpioWrite(GC::GPIO,GC::SBJ_READY_PORT, 1);
                    confirmed_controllers.clear();
                    needed_controllers.clear();
                    for(auto& p : trials[trialorder.front()].visual_stimuli){
                        needed_controllers.push_back(p.controller_target);
                    }
                    switchTState(T_INFORM_CONTROLLERS);
                }
                if(stim_index == 0) {
                    start = std::chrono::high_resolution_clock::now();
                    responsecontroller.start(start);
                    //std::cout << "\r[DEBUG] Strt time: " << start) << endl;
                }
            }

            // In questo stato il master invia agli slave i parametri degli stimoli visivi da presentare,
            // attende la conferma di ricezione da tutti i controller necessari prima di procedere.
            else if(tstate==T_INFORM_CONTROLLERS){
                cout << "\rT: Inform controllers about trial Visual stimulu sequence"<< std::endl;
                // Iforma i target controller della rispettiva sequanza di stimoli V da eseguire
                informControllers(trials[trialorder.front()]);
                bool allverified=true;
                for(auto& p : trials[trialorder.front()].visual_stimuli){
                    if(find(confirmed_controllers.begin(),confirmed_controllers.end(),p.controller_target)==confirmed_controllers.end()) allverified=false;
                }
                if(allverified){
                    confirmed_controllers.clear();
                    switchTState(T_TRIAL_ON);
                    thefirsttrial = true;
                    lgGpioWrite(GC::GPIO,GC::SBJ_READY_PORT ,0);
                    lgGpioWrite(GC::GPIO,GC::TRIAL_RESET_PORT,0);
                    lgGpioWrite(GC::GPIO,GC::RESPONSE_INTERRUPT_PORT,0);
                }
                else cout << "FAILED VERIFICATION of SLAVE CONTROLLERS\n";
                // else if(trial_modalities[stim_index] == "A") {
                //     cout << "\r[DEBUG] Inform controller about 'A' stimulus" << endl;
                //     Visual_Stimulus v;
                //     v.onset = trials[trialorder.front()].auditory_stimuli[audio_index].onset;
                //     v.offset = trials[trialorder.front()].auditory_stimuli[audio_index].offset;
                //     v.isi = trials[trialorder.front()].auditory_stimuli[audio_index].isi;
                //     v.pixels = {}; // vettore vuoto: non ci sono immagini da generare
                //     informControllers(v);
                //     cout << "\rINFORM ABOUT 'A' STIMULUS" << endl;
                //     switchTState(T_TRIAL_ON);
                //     thefirsttrial = true;
                // }
            }

            // Stato di setup dello stimolo corrente
            // In questo stato vengono inizializzati timer e raccolta risposte per lo stimolo corrente.
            // La transizione a T_WAIT_FOR_END è immediata: qui non avviene attesa, ma solo setup e avvio.
            else if(tstate==T_TRIAL_ON){
                // responsecontroller.clear();
                lgGpioWrite(GC::GPIO,GC::TRIAL_START_PORT,1);
                start_trial = std::chrono::high_resolution_clock::now();
                start = std::chrono::high_resolution_clock::now();
                responsecontroller.start(start);
                //std::cout << "\r[DEBUG] Strt time: " << start) << endl;
                cout << "\rT: Trial on (note wait doesn't inform)" << std::endl;
                // DEBUG: stampa modalità e JSON stimolo corrente
                // cout << "\r[DEBUG] Modalità stimolo corrente: " << trial_modalities[stim_index] << endl;
                // if (trial_modalities[stim_index] == "V") {
                //     cout << "\r[DEBUG] JSON stimolo VISIVO: " << trials[trialorder.front()].visual_stimuli[visual_index].toJSON() << endl;
                // } else if (trial_modalities[stim_index] == "A") {
                //     cout << "\r[DEBUG] JSON stimolo ACUSTICO: " << trials[trialorder.front()].auditory_stimuli[audio_index].toJSON() << endl;
                // } else if (trial_modalities[stim_index] == "AV") {
                //     cout << "\r[DEBUG] JSON stimolo VISIVO: " << trials[trialorder.front()].visual_stimuli[visual_index].toJSON() << endl;
                //     cout << "\r[DEBUG] JSON stimolo ACUSTICO: " << trials[trialorder.front()].auditory_stimuli[audio_index].toJSON() << endl;
                // }
                // SDL_Init(SDL_INIT_EVENTS); // SDL library for rvents management inizialization
                // inizialation of libevdev structure
                switchTState(T_WAIT_FOR_END);
            }
            else if(tstate==T_WAIT_FOR_END){
                this_time = std::chrono::high_resolution_clock::now();
                long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start).count();
                //long elapsed_trial = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start_trial).count();
                // std::cout << "\r[DEBUG] Elapsed time PRE: " << elapsed << endl;
                static struct libevdev *dev = NULL;
                if(thefirsttrial && dev == NULL){
                    responsecontroller.init_keyboard("/dev/input/event5", &dev);  // Passa il puntatore a `dev` con focus su event0 (dispositivo tastiera)
                }
                // Confronta il cronometro con la durata del singolo stimolo (stim_duration)
                if(elapsed >= trials[trialorder.front()].total_duration) {
                    switchTState(T_END);
                }
                else if((responsecontroller.processEvents(this_time, dev))){
                    cout << "\r[PLUTO]" << endl;
                    if(GC::INT_EXECUTION) { // exit the execution of the experiment if ESC button is pressed (i.e., if INIT_EXECUTION has been switchen to 'true' inside processEvents()
                        estate = E_LOAD_CONFIGURATION;
                        tstate = T_STANDBY;
                        std::cout << "\rEXECUTION INTERRUPTED\n";
                    }
                    // std::cout << "\rElapsed " << to_string(elapsed) << " vs stim_duration " << to_string(stim_duration);
                    // lgGpioWrite(GC::GPIO,GC::RESPONSE_INTERRUPT_PORT,1); // tell the slave to interrupt the visual cue execution           
                }
                else { // the trial is on going: gestisci output acustico secondo il flag use_whitenoise
                    std::vector<Auditory_Stimulus>& astim = trials[trialorder.front()].auditory_stimuli;
                    if (use_whitenoise) {
                        // cout << "\rOK USE WN" << endl;
                        // White noise: come ora, random burst

                        // qui il ciclo com'è scritto non puo eseguire correttamente ogni singolo stimolo acustico in modo sequenziale:
                        // crea ad ogni ciclo dello stato T_WAIT_FOR_END un vettore degli stimoli acustici da eseguire per il trial corrente e poi con un puntatore
                        // scorre ciclicamente su tutti gli stimoli del vettore e lo fa ad ogni cilo dello stato (INUTILE)
                        // COME DEVE FUNZIONARE: estraggo la sequenza di stimoli acustici del trial > usando elapsed devo verificare ad ogni ciclo dello stato se
                        // sono dentro all'intervallo di esecuzione di uno degli stimoli (e quindi attivare l'audio) e nel mentre ad ogni ciclo anche monitorare gli eventi da tastiera (e gestirli)
                        // oppure se non ricado nell'intervallo [onset-offset] di

                        // finche elapsed ricade all'interno dll'intervallo <onset-offset> di uno stimolo, contunuare a produrre il suono deisderato
                        // appena elapsed esce fuori (cioe > offset ma < onset dllo stimolo dopo) uscire dall'esecuzione audio e cilcare sulla ricezione
                        // e gestione di input da tastiera: praticmante ascoltare gli input da tastiiera soltanto nell'intervallo di ISI fra un offset e l'onset successivo
                        // Usicre dallo stato quando 1) o l'ultimo stimolo n otdine cronologico è stato eseguito oppure 2) quando si è raggiunto il tempo di
                        // durata totale del tiral

                        // come sfruttare i vettore di stimoli vector<Auditory_Stimulus>& astim = trials[trialorder.front()].auditory_stimuli???
                        // come ciclare sugli stioli e fermarsi all'esecuzione di un solo stimolo alla volta senza rallentare il codice??

                        for(auto& as : astim){
                            cout << "\r[DEBUG] ONSET:" << as.onset << " | OFFSET:" << as.offset << endl;
                            if(as.state==Auditory_Stimulus::DURING){
                                if(elapsed>as.offset){
                                    as.state=Auditory_Stimulus::PRE;
                                }
                            }
                            else if((elapsed>as.onset)&&(elapsed<as.offset)){
                                if(as.state==Auditory_Stimulus::PRE){
                                    as.state=Auditory_Stimulus::DURING;
                                }
                                cout << "\r[DEBUG] DURING" << endl;
                                int randomValue = rand() % 2;
                                lgGpioWrite(GC::GPIO,as.channel,randomValue);
                            }
                        }
                        // std::cout << "\rDEBUG: whithe noise ON" << std::endl;
                    } else {
                        // Nota pura: usa AuditoryController (PWM)
                        auditorycontroller.update(elapsed, astim);
                    }
                    // long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start).count();
                    // auditorycontroller.update(elapsed,trials[trialorder.front()].auditory_stimuli);
                }
                thefirsttrial = false;
            }
            else if(tstate==T_END){
                cout << "\rT: Trial ends" << std::endl;
                 // previusly set at 1 as soon as the subject had clucked a keyboard response button
                lgGpioWrite(GC::GPIO,GC::TRIAL_START_PORT,0);
                responsecontroller.resetLastResponse();
                switchEState(E_FINISH_TRIAL);
                switchTState(T_STANDBY);
            }
        }
        else if(estate==E_FINISH_TRIAL){
            cout << "\rE: Finishing Stimulus " << stim_index << std::endl;
            cout << "\r[DEBUG] V idx = " << visual_index << endl;
            cout << "\r[DEBUG] A idx = " << audio_index << endl;

            // Scrivi l'output dello stimolo corrente (opzionale: puoi accumulare e scrivere tutto a fine macro-trial)
            // Se vuoi scrivere solo a fine macro-trial, sposta questa logica dopo il ciclo

            // stim_index++; // Incrementa l'indice dello stimolo corrente
            // Aggiorna inici locali per ciascuna modalità
            if(trial_modalities[stim_index] == "V") visual_index++;
            else if(trial_modalities[stim_index] == "A") audio_index++;
            else if(trial_modalities[stim_index] == "AV") {visual_index++; audio_index++;}
            stim_index++;
            // Se ci sono altri stimoli nel macro-trial, passa al prossimo stimolo
            if(stim_index < (int)trial_modalities.size()) {
                thefirsttrial = false;
                switchEState(E_RUNNING_TRIAL);
                switchTState(T_STANDBY);
                cout << "\r-----------------------------------------" << std::endl;
                cout << "\r         NEXT STIMULUS IN BLOCK          " << std::endl;
                cout << "\r-----------------------------------------" << std::endl;
            }
            // Se tutti gli stimoli del macro-trial sono stati eseguiti, chiudi il trial
            else {
                stim_index = 0;
                visual_index = 0;
                audio_index = 0;
                if(writeoutput){
                    GC::appendToFile(outputfilename,getTrialOutputJSON(trials[trialorder.front()]));
                    GC::appendToFile(outputfilename,"]");
                }
                trialorder.pop_front();
                if(GC::USE_INTERFACE_NOT_FILE) estate=E_LOAD_CONFIGURATION;
                else switchEState(E_END);
                thefirsttrial=false;
                cout << "\r******************************************" << std::endl;
                cout << "\r                 END EXPERIMENT               " << std::endl;
                cout << "\r******************************************" << std::endl;
            }
        }
    }

}

void Experiment::switchEState(E_STATE newestate)
{
    cout << "\r> switching estate from "<< to_string(estate) << " to " << to_string(newestate) << std::endl;
    estate=newestate;
}

void Experiment::switchTState(T_STATE newtstate)
{
    cout << "\r> switching tstate from "<< to_string(tstate) << " to " << to_string(newtstate) << std::endl;
    tstate=newtstate;
}

// Informa i controller slave sugli stimoli visivi del trial corrente.
// Stabilisce una connessione TCP con i controller, legge il nome del client,
// verifica se il controller è tra quelli richiesti, e invia il messaggio JSON con gli stimoli.
bool Experiment::informControllers(Trial &t)
{
    try{
        asio::io_context io_context;
        // slave 1
        tcp::acceptor acceptor_slave1(io_context, tcp::endpoint(tcp::v4(), 13));
        tcp::socket socket_slave1(io_context);
        acceptor_slave1.accept(socket_slave1);
        // // slave 2
        // tcp::acceptor acceptor_slave2(io_context, tcp::endpoint(tcp::v4(), 14));
        // tcp::socket socket_slave2(io_context);
        // acceptor_slave2.accept(socket_slave2);

        // slave 1 tcp connection management
        string client_name1;
        GC::readMessageFromSocket(socket_slave1, client_name1, GC::message_delimiter);
        std::cout << "\rClient name: " << client_name1 << "\n";

        confirmed_controllers.push_back(client_name1);
        std::cout << std::endl;
        std::cout << "\r> Connection from " << socket_slave1.remote_endpoint().address().to_string() << " named " << client_name1 << "> DONE!" << std::endl;
        string message1 = "";
        message1 = messageTrialJSON(client_name1); // Solo lo stimolo per il controller target
        GC::writeMessageToSocket(socket_slave1, message1, GC::message_delimiter);
        std::cout << "\r[DEBUG] Messaggio inviato al target controller: " << message1 << std::endl;
        // // slave 2 tcp connection management
        // string client_name2;
        // GC::readMessageFromSocket(socket_slave2, client_name2, GC::message_delimiter);
        // confirmed_controllers.push_back(client_name2);
        // std::cout << std::endl;
        // std::cout << "\r> Connection from " << socket_slave2.remote_endpoint().address().to_string() << " named " << client_name2 << "> DONE!" << std::endl;
        // string message2 = "";
        // message2 = messageTrialJSON(client_name2, stim); // Solo lo stimolo per il controller target
        // GC::writeMessageToSocket(socket_slave2, message2, GC::message_delimiter);
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
    }
    return true;
}

bool Experiment::verifyController(string type, string controllername)
{
    if(type=="VISUAL"){

    }
    else if(type=="AUDITORY"){

    }
    return true;
}

// Generazione di un messaggio JSON contenente gli stimoli visivi del trial corrente,
// filtrati per il controller target specificato.
string Experiment::messageTrialJSON(string controller_target)
{
    string toreturn ="{";
    toreturn+= "\"STIMULI\": [";
    bool thefirst=true;
    for(auto& v : trials[trialorder.front()].visual_stimuli){
        if (v.controller_target == controller_target) {
            if (thefirst) thefirst=false;
            else toreturn+=",";
            toreturn+=v.toJSON();
        }
    }
    toreturn+="]";
    toreturn+="}";
    return toreturn;
}

