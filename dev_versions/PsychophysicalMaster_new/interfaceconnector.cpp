#include "interfaceconnector.h"
#include <iostream>
#include "asio.hpp"
#include "gc.h"

using asio::ip::tcp;

InterfaceConnector::InterfaceConnector() : experimentJSON("{}") {}

InterfaceConnector::CONNECTION_OUTCOME InterfaceConnector::waitForInterfaceConnection()
{
    asio::io_context io_context;
    tcp::acceptor acceptor(io_context,tcp::endpoint(tcp::v4(),13));
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    string client_name;
    GC::readMessageFromSocket(socket,client_name,GC::message_delimiter);
    if(client_name=="INTERFACE"){
        GC::readMessageFromSocket(socket,experimentJSON,GC::message_delimiter);
        return SUCCESS;
    }

    return INPROGRESS;
}

void InterfaceConnector::reset()
{
    experimentJSON="{}";
}

