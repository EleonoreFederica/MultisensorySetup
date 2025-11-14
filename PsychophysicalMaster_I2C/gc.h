#ifndef GC_H
#define GC_H

#pragma once
#include "document.h"
#include <string>
#include <list>
#include "asio.hpp"
#include <lgpio.h>

using namespace std;
using asio::ip::tcp;

class GC
{
public:
    GC();

    const static char message_delimiter='#';

    static bool loadConfig(string _filename);
    static bool loadJSONFromString(rapidjson::Document& doc,string& jsonstring);
    static bool loadJSONFromFile(rapidjson::Document& doc,string filename);
    static string qenc(string to_encapsulate_in_quotes);
    static string getJSONOfValue(rapidjson::Value& v);
    static string getJSONStringFromFile(string filename);
    static string getTimeStamp();
    static bool initI2C(); // initialize I2C bus
    static void closeI2C();
    static bool readMessageFromSocket(tcp::socket &socket, string &into_this_string, char delimiter);
    static bool writeMessageToSocket(asio::ip::tcp::socket &socket, string &from_this_string, char delimiter);
    static bool writeMessageArduino(std::string &data);
    static bool appendToFile(string& filename,string str);
    static asio::ip::tcp::socket* createNewSocket(int port);
    static void cbf(int e, lgGpioAlert_p evt, void *data);

    // static int kbhit() // check for a possible input selected from the keyboard
    // {
    //     struct timeval tv = { 0L, 0L };
    //     fd_set fds;
    //     int fd = open("/dev/input/event1", O_RDONLY); // Apri il dispositivo della tastiera

    //     if (fd == -1) {
    //         return 0; // Errore nell'aprire il dispositivo
    //     }

    //     FD_ZERO(&fds);
    //     FD_SET(fd, &fds); // Aggiungi il file descriptor del dispositivo della tastiera

    //     // Se c'è un evento di input sulla tastiera, selezionerà il fd
    //     int result = select(fd + 1, &fds, NULL, NULL, &tv);

    //     close(fd); // Chiudi il file descriptor dopo l'uso

    //     return result > 0; // Restituisci 1 se c'è stato un input, altrimenti 0
    // }

    static bool INT_EXECUTION;
    static int DEFAULT_TRIAL_DURATION;
    static list<string> VISUAL_CONTROLLER_NAMES;
    static bool USE_INTERFACE_NOT_FILE;
    static bool USE_PEDAL_CONTROL;
    static string EXPERIMENT_FILE_IF_USED;
    static int TRIAL_START_PORT;
    static int TRIAL_RESET_PORT;
    static int PEDAL_PORT;
    static int RESPONSE_INTERRUPT_PORT;
    static int SBJ_READY_PORT;

    static int GPIO;



private:
    static inline int i2c_fd = -1; // file descriptor of I2C bus
    static constexpr const char* i2c_device = "/dev/i2c-1"; //device patch
    static constexpr int arduino_address = 0x08; // Arduino I2C addresss

};

inline string GC::qenc(string to_encapsulate_in_quotes)
{
    return "\""+to_encapsulate_in_quotes+"\"";
}



#endif // GC_H
