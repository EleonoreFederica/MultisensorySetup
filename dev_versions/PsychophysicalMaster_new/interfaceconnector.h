#ifndef INTERFACECONNECTOR_H
#define INTERFACECONNECTOR_H

#include <string>
#include "asio.hpp"

using namespace std;

//This class connects with the gui. The computer running the gui has to connect to the computer via wifi first
class InterfaceConnector
{
public:
    enum CONNECTION_OUTCOME{FAILED,INPROGRESS,SUCCESS};
    InterfaceConnector();


    CONNECTION_OUTCOME waitForInterfaceConnection();
    void reset();

    string experimentJSON;


};

#endif // INTERFACECONNECTOR_H
