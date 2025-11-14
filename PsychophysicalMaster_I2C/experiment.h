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

    void createTrialOrder(string rule="random_without_replacement"); // random_without_replacement, random_with_replacement, sequential

    void runExperiment();
    void switchEState(E_STATE newestate);
    void switchTState(T_STATE newtstate);

    bool informControllers(Trial& t);
    bool verifyController(string type,string controllername);
    bool informVisualControllers(Trial& t);
    bool informAudioControllers(Trial& t);


    // string getTestingVisualStimulusString(string controller_target);
    // string createTrialJSON(string controller_target);
    string messageVJSON(string controller_target);
    string messageAJSON();

    string subjectname="NULLSUBJECT";
    string experimentname="NULLEXPERIMENT";
    string outputfilename="NULLFILE"; //appends data to this file
    int number_of_loops=1;
    string trialordering="random_without_replacement"; // random_without_replacement, random_with_replacement, sequential
    string response="[NULL]";
    bool writeoutput=true;

    E_STATE estate=E_LOAD_CONFIGURATION;
    T_STATE tstate=T_INFORM_CONTROLLERS;

    AuditoryController auditorycontroller;
    ResponseController responsecontroller;
    InterfaceConnector interfaceconnector;
    vector<string> confirmed_controllers;
    vector<string> needed_controllers;

    vector<Trial> trials;
    list<int> trialorder;

    // asio::ip::tcp::socket* socket;
};


#endif // EXPERIMENT_H
