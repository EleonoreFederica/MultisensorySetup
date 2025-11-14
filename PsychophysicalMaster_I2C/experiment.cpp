#include "experiment.h"
#include "gc.h"
#include <iostream>
#include "asio.hpp"
#include "stdio.h"
#include <libevdev-1.0/libevdev/libevdev.h>


using namespace std;
using asio::ip::tcp;

Experiment::Experiment() {}

bool Experiment::fromJSON(string& jsonstring)
{

    rapidjson::Document doc;

    cout << "\rLoading experiment from json...";

    if(!GC::loadJSONFromString(doc,jsonstring)){cout << "ERROR LOADING EXPERIMENT\n"; return false;}
    if(doc.HasMember("SUBJECTNAME")) subjectname = doc["SUBJECTNAME"].GetString();
    if(doc.HasMember("NUMBER_OF_LOOPS")) number_of_loops = doc["NUMBER_OF_LOOPS"].GetInt();
    if(doc.HasMember("TRIALORDERING")) trialordering = doc["TRIALORDERING"].GetString();
    if(doc.HasMember("WRITEOUTPUT")) writeoutput = doc["WRITEOUTPUT"].GetBool();

    cout << "loaded header...\n ";

    if(doc.HasMember("TRIALS")){
        trials.clear();
        for(auto& t : doc["TRIALS"].GetArray()){
            Trial tr;
            string jsonstring = GC::getJSONOfValue(t);
            tr.fromJSON(jsonstring);
            trials.push_back(tr);
        }
    }
    return true;
}

void Experiment::reset()
{
    estate=E_LOAD_CONFIGURATION;
    tstate=T_STANDBY;
}

string Experiment::getTrialOutputJSON(Trial &t)
{
    string toreturn ="{";
    toreturn+="     "+GC::qenc("SUBJECTNAME") + ": " + GC::qenc(subjectname) + ",";
    toreturn+="     "+GC::qenc("TIMESTAMP") + ": " + GC::getTimeStamp() + ",";
    toreturn+="     "+GC::qenc("RESPONSES") + ": "  + responsecontroller.getResponsesJSONArray() + ",";
    toreturn+="     "+GC::qenc("TRIAL") + ": " + t.toJSON();
    toreturn+="}";
    return toreturn;
}

void Experiment::createTrialOrder(string rule) //random_without_replacement, random_with_replacement, sequential
{
    trialorder.clear();
    if(rule=="random_without_replacement"){
        vector<int> source; for(size_t i=0;i<trials.size();i++) source.push_back(i);
        while(source.size()>0){
            int pick = rand()%source.size();
            trialorder.push_back(pick);
            source.erase(source.begin() + pick);
        }
    }
    else if(rule=="random_with_replacement"){
        for(size_t i=0;i<trials.size();i++) trialorder.push_back(rand()%trials.size());
    }
    else if(rule=="sequential"){
        for(size_t i=0;i<trials.size();i++) trialorder.push_back(static_cast<int>(i));
    }
}

void Experiment::runExperiment()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto this_time = std::chrono::high_resolution_clock::now();
    bool thefirsttrial=true;
    // bool firstauditory=true;
    confirmed_controllers.clear();
    while(estate!=E_END){
        if(estate==E_LOAD_CONFIGURATION){
            GC::INT_EXECUTION = false;
            lgGpioWrite(GC::GPIO,GC::TRIAL_RESET_PORT,0);
            if (thefirsttrial){
                lgGpioWrite(GC::GPIO,GC::RESPONSE_INTERRUPT_PORT,0);
                cout << "\rE: Load configuration\n";
            }

            string experimentjson="{}";
            // case: use the Interface configuration transmission (default)
            if(GC::USE_INTERFACE_NOT_FILE){
                if(interfaceconnector.waitForInterfaceConnection()==InterfaceConnector::SUCCESS){
                    experimentjson = interfaceconnector.experimentJSON;
                    cout << "\rreceived experimentjson " << experimentjson << "\n";
                }
            }
            // case: not use the Interface but directly the sample_exp
            else experimentjson = GC::getJSONStringFromFile(GC::EXPERIMENT_FILE_IF_USED);
            if(experimentjson!="{}"){
                cout << "\rLoading json for experiment...";
                fromJSON(experimentjson);
                cout << "done!\n";
                string timestamp = GC::getTimeStamp();
                string experimentfilename = timestamp+"experiment.json";
                // GC::appendToFile(experimentfilename,experimentjson);
                outputfilename = timestamp+subjectname+".json";
                if(writeoutput) GC::appendToFile(outputfilename,"[");
                cout << "Done loading successfully. Switching to trial ordering...\n";
                switchEState(E_ORDER_TRIALS);
            }

            // Inizialization I2C
            if (!GC::initI2C()) {
                std::cout << "<rError on I2C iniialization\n" << endl;
            }

            // thefirsttrial=false;
        }
        else if(estate==E_ORDER_TRIALS){
            // thefirsttrial=true;
            cout << "\rE: Create trial order by " << trialordering << "\n";
            createTrialOrder(trialordering);
            if(trialorder.size()>0){
                switchEState(E_RUNNING_TRIAL);
                switchTState(T_STANDBY);
            }
            else {cout << "ERROR: trialorder is empty after ordering\n"; switchEState(E_END);}
        }
        else if(estate==E_RUNNING_TRIAL){
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
            }
            else if(tstate==T_INFORM_CONTROLLERS){
                cout << "\rT: Inform controllers about trial# " << to_string(trialorder.front()) << std::endl;
                informControllers(trials[trialorder.front()]);
                bool allverified=true;
                for(auto& p : trials[trialorder.front()].visual_stimuli){
                    if(find(confirmed_controllers.begin(),confirmed_controllers.end(),p.controller_target)==confirmed_controllers.end()) allverified=false;
                }
                if(allverified){
                    confirmed_controllers.clear();
                    switchTState(T_TRIAL_ON);
                    start = std::chrono::high_resolution_clock::now();
                    // thefirsttrial = true;
                    lgGpioWrite(GC::GPIO,GC::SBJ_READY_PORT ,0);
                    lgGpioWrite(GC::GPIO,GC::TRIAL_RESET_PORT,0);
                    lgGpioWrite(GC::GPIO,GC::RESPONSE_INTERRUPT_PORT,0);
                }
                else cout << "FAILED VERIFICATION of SLAVE CONTROLLERS\n";

            }
            else if(tstate==T_TRIAL_ON){
                // responsecontroller.clear_stdin();
                // trial starting awaiting time: 2000ms
                if(thefirsttrial){
                    std::cout << "\r>WAIT FOR 2000ms UNTIL EXPERIMENT START..." << std::endl;
                    const int preparation_time = 2000;
                    this_time = std::chrono::high_resolution_clock::now();
                    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start).count();
                    while(elapsed <= preparation_time) {
                        this_time = std::chrono::high_resolution_clock::now();
                        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start).count();
                    }
                }
                lgGpioWrite(GC::GPIO,GC::TRIAL_START_PORT,1);
                start = std::chrono::high_resolution_clock::now();
                responsecontroller.start(start);
                cout << "\rT: Trial on (note wait doesn't inform)" << std::endl;
                // SDL_Init(SDL_INIT_EVENTS); // SDL library for rvents management inizialization
                // inizialization of libevdev structure

                switchTState(T_WAIT_FOR_END);
            }
            else if(tstate==T_WAIT_FOR_END){
                this_time = std::chrono::high_resolution_clock::now();
                long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start).count();
                static struct libevdev *dev = NULL;
                if(thefirsttrial && dev == NULL){
                    responsecontroller.init_keyboard("/dev/input/event4", &dev);  // Passa il puntatore a `dev` con focus su event0 (dispositivo tastiera)
                }
                if (elapsed>=trials[trialorder.front()].duration){
                    switchTState(T_END);
                }
                if (responsecontroller.processEvents(this_time, dev)){
                    if(GC::INT_EXECUTION) { // exit the execution of the experiment if ESC button is pressed (i.e., if INIT_EXECUTION has been switchen to 'true' inside processEvents()
                        estate = E_LOAD_CONFIGURATION;
                        tstate = T_STANDBY;
                        std::cout << "\rEXECUTION INTERRUPTED\n";
                    }
                    // lgGpioWrite(GC::GPIO,GC::RESPONSE_INTERRUPT_PORT,1); // tell the slave to interrupt the visual cue execution
                    // cout << "\rELAPSED " << to_string(elapsed) << "vs " << to_string(trials[trialorder.front()].duration);
                }
                else { // the trial is on going: generate white nise on the target channel
                    list<Auditory_Stimulus> astim = trials[trialorder.front()].auditory_stimuli;
                    // for(auto& as : astim){
                    //     if(as.state==Auditory_Stimulus::DURING){
                    //         if(elapsed>as.offset){
                    //             as.state=Auditory_Stimulus::PRE;
                    //             std::cout << "\r[DEBUG] state PRE | elapsed: " << elapsed << std::endl;
                    //         }
                    //     }
                    //     else if((elapsed>as.onset)&&(elapsed<as.offset)){
                    //         if(as.state==Auditory_Stimulus::PRE){
                    //             as.state=Auditory_Stimulus::DURING;
                    //             std::cout << "\r[DEBUG] state DURING | elapsed: " << elapsed << std::endl;
                    //             int randomValue = rand() % 2;
                    //             lgGpioWrite(GC::GPIO,as.channel,randomValue);
                    //         }
                    //     }

                    // }
                    for(auto& as : astim) {
                        if(elapsed >= as.onset && elapsed < as.offset) {
                            if(as.state != Auditory_Stimulus::DURING) {
                                as.state = Auditory_Stimulus::DURING;
                                // std::cout << "\r[DEBUG] state DURING | elapsed: " << elapsed << std::endl;
                            }
                            int randomValue = rand() % 2;
                            lgGpioWrite(GC::GPIO,as.channel,randomValue);
                            } else {
                            if(as.state != Auditory_Stimulus::PRE) {
                                as.state = Auditory_Stimulus::PRE;
                                // std::cout << "\r[DEBUG] state PRE | elapsed: " << elapsed << std::endl;
                            }
                            lgGpioWrite(GC::GPIO,as.channel,0);
                        }
                    }
                    // long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start).count();
                    // auditorycontroller.update(elapsed,trials[trialorder.front()].auditory_stimuli);
                }
                // thefirsttrial = false;
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
            cout << "\rE: Finishing Trial" << std::endl;

            if(writeoutput){ //write output
                GC::appendToFile(outputfilename,getTrialOutputJSON(trials[trialorder.front()]));
                if((trialorder.size()-1)>0) {
                    GC::appendToFile(outputfilename,",\n");
                }
            }

            trialorder.pop_front();
            if(trialorder.size()>0) { // other trials available to be executed from te list...
                thefirsttrial = false;
                switchEState(E_RUNNING_TRIAL);
                cout << "\r-----------------------------------------" << std::endl;
                cout << "\r                 END TRIAL               " << std::endl;
                cout << "\r-----------------------------------------" << std::endl;
            } else { // no more trials in the list for this loop...
                if(--number_of_loops>0) { // ...but one more loop to be executed
                    switchEState(E_ORDER_TRIALS);
                    cout << "\r-----------------------------------------" << std::endl;
                    cout << "\r                 END TRIAL               " << std::endl;
                    cout << "\r-----------------------------------------" << std::endl;
                    std::cout << "\r------------START A NEW LOOP-------------\n";
                }
                else{ // no more trials and no more loops...
                    if(writeoutput) GC::appendToFile(outputfilename,"]");
                    if(GC::USE_INTERFACE_NOT_FILE) estate=E_LOAD_CONFIGURATION;
                    else switchEState(E_END);
                    thefirsttrial = true;
                    cout << "\r******************************************" << std::endl;
                    cout << "\r                 END EXPERIMENT               " << std::endl;
                    cout << "\r******************************************" << std::endl;
                }
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

bool Experiment::informControllers(Trial &t)
{
    try{
        asio::io_context io_context;
        // slave 1
        tcp::acceptor acceptor_slave1(io_context,tcp::endpoint(tcp::v4(),13));
        tcp::socket socket_slave1(io_context);
        acceptor_slave1.accept(socket_slave1);
        // slave 2
        tcp::acceptor acceptor_slave2(io_context,tcp::endpoint(tcp::v4(),14));
        tcp::socket socket_slave2(io_context);
        acceptor_slave2.accept(socket_slave2);

        // slave 1 tcp connection management
        string client_name1;
        GC::readMessageFromSocket(socket_slave1,client_name1,GC::message_delimiter);
        confirmed_controllers.push_back(client_name1);
        std::cout << std::endl;
        std::cout << "\r> Connection from " << socket_slave1.remote_endpoint().address().to_string() << " named " << client_name1 << "> DONE!" << std::endl;
        // std::copy(confirmed_controllers.begin(), confirmed_controllers.end(), std::ostream_iterator<std::string>(std::cout, " "));
        string message1 = ""; // creation of empty message if slave is not needed in this trial
        message1=messageVJSON(client_name1); // in the form json: { "TRIAL_DURATION": <value>, "STIMULI": [{stim_1},{stim_2},...,{stim_last}]}
        GC::writeMessageToSocket(socket_slave1,message1,GC::message_delimiter);

        // std::cout << "Messaggio inviato: " << message1 << std::endl;

        // slave 2 tcp connection management
        string client_name2;
        GC::readMessageFromSocket(socket_slave2,client_name2,GC::message_delimiter);
        confirmed_controllers.push_back(client_name2);
        std::cout << std::endl;
        std::cout << "\r> Connection from " << socket_slave2.remote_endpoint().address().to_string() << " named " << client_name2 << "> DONE!"  << std::endl;
        // std::copy(confirmed_controllers.begin(), confirmed_controllers.end(), std::ostream_iterator<std::string>(std::cout, " "));
        string message2 = ""; // creation of empty message if slave is not needed in this trial
        message2=messageVJSON(client_name2); // in the form json: { "TRIAL_DURATION": <value>, "STIMULI": [{stim_1},{stim_2},...,{stim_last}]}
        GC::writeMessageToSocket(socket_slave2,message2,GC::message_delimiter);

        // std::cout << "Messaggio inviato: " << message2 << std::endl;

        string message3 = messageAJSON();
        GC::writeMessageArduino(message3);
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

string Experiment::messageAJSON()
{
    string toreturn ="{";
    for(auto& a : trials[trialorder.front()].auditory_stimuli){
        toreturn+=a.toJSON();
        break;
    }
    toreturn+="}";
    return toreturn;
}
string Experiment::messageVJSON(string controller_target)
{
    string toreturn ="{";
    toreturn+= GC::qenc("DURATION")+": "+to_string(trials[trialorder.front()].duration)+",";
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
