#include "responsecontroller.h"
#include "gc.h"
#include <iostream>
#include <linux/input.h>
// #include "conio.h"  //THIS IS FOR WINDOWS

//FOLLOWING IMPLEMENT CONIO FUNCTIONALITY FOR LINUX
//BEGIN LINUX PORTION
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
// #include <sys/select.h>
// #include <ncurses.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <chrono>
#include <termios.h>

// implements a ResponseController class that handles keyboard inputs during an experiment,
// monitoring key events (keystrokes) and saving the time at which they occur relative to the start of the experiment

#define SIZE 9
#define ESC_BUTTON 1

struct termios orig_termios;
vector keyboard_side_R = {KEY_I, KEY_O, KEY_P, KEY_J, KEY_K, KEY_L, KEY_N, KEY_M, KEY_COMMA};
vector keyboard_side_L = {KEY_Q, KEY_W, KEY_E, KEY_A, KEY_S, KEY_D, KEY_Z, KEY_X, KEY_C};
long lastResponseTime = 0;
void reset_terminal_mode(){
    tcsetattr(0, TCSANOW, &orig_termios);
}
void set_conio_terminal_mode()
{
    struct termios new_termios;
    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));
    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

void ResponseController::clear_stdin() {
    tcflush(0, TCIFLUSH); // Svuota il buffer di input
}


// check for a possible key button pressed in a non-blocking way
int kbhit(struct libevdev *dev)
{
    if (!dev) {
        std::cerr << "\rError: dev == NULL!\n";
        return -1;
    }
    struct input_event ev;
    int rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    if((rc < 0) && (rc != -EAGAIN)) { // failed reading the event
        std::cout << "\rError in event reading: %d " << rc << "\n";
        return 0;
    }
    if (rc == 0 && ev.type == EV_KEY && ev.value == 1) {  // success reading the key btn pressure
        return ev.code;
    }
    return 0;  //
}

const char* getKeySide(int code)
// returns a string "Left" if a button on left side of keyboard is pressed
// returns a string "Right" if a button on right side of keyboard is pressed
// returns string "unknown" if any other buttons is pressed
{
    for (int i = 0; i < SIZE; i++) {
        if (code == keyboard_side_L[i]) {
            return "LEFT";
        } else if (code == keyboard_side_R[i]) {
            return "RIGHT";
        }
    }
    return "UNKNOWN"; // Se il tasto non è in nessun gruppo
}

// int kbhit() // check for a possible input selected from the keyboard
// {
//     struct timeval tv = { 0L, 0L };
//     fd_set fds;
//     FD_ZERO(&fds);
//     FD_SET(0, &fds);
//     return select(1, &fds, NULL, NULL, &tv)> 0;
// }

// int getch()
// {
//     int r;
//     unsigned char c;

//     // read a single char from terminal in raw mode
//     if ((r = read(0, &c, sizeof(c))) < 0) {
//         return r;
//     } else
//     {return c; };
// }
//END LINUX PORTION



ResponseController::ResponseController() {}

void ResponseController::reset()
{
    responses.clear();
    lastResponseTime = 0;
}

void ResponseController::start(std::chrono::system_clock::time_point _start)
{
    reset();
    start_time = _start;
    set_conio_terminal_mode();
}

void ResponseController::init_keyboard(const char *device_path, struct libevdev **dev)
// open and read the identifier (file descriptor) of the device from the path
// store in the variable fd. Then it has to be associated to the fd instance
// of libevdev *dev structure (dev.fd) through libevdev_new_from_fd function
{
    int fd = open(device_path, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("\rError in opening the device\n");
        return;
    }
    if (libevdev_new_from_fd(fd, dev) < 0) {
        std::cout << "\nError in iniztializing libevdev\n";
        close(fd);
        return;
    }
}

bool ResponseController::processEvents(std::chrono::system_clock::time_point this_time, struct libevdev *dev)
{
    int keycode = kbhit(dev); // if successful reading then store the ev.code of that button
    if(keycode) { // manage the keyboard event only if something has been detected
        std::cout << "\nkeyboard hit\n";
        if(keycode == ESC_BUTTON) { // if the ESC button is pressed during exporiment execution, the global constant INT_EXECUTION will detemine the immediate exiting from experiment trial loop
            GC::INT_EXECUTION = true;
        }
        long currentElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start_time).count();

        // Controllo del debounce
        if (currentElapsed - lastResponseTime < DEBOUNCE_INTERVAL) {
            return false; // Input ignorato
        }
        // Registra l'input e aggiorna il tempo dell'ultimo input
        responses.push_back(Response(currentElapsed, getKeySide(keycode))); // append to response array the RT and the sgring
        lastResponseTime = currentElapsed;
        return true;
    }

    // initscr();              // Inizializza la libreria ncurses
    // timeout(0);             // Imposta il timeout a 0 per non bloccare
    // int ch = getch();       // Legge un carattere da tastiera (non bloccante)

    // if (ch != ERR) {        // Se c'è stato un input
    //     long currentElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(this_time-start_time).count();

    //     // Controllo del debounce
    //     if (currentElapsed - lastResponseTime < DEBOUNCE_INTERVAL) {
    //         return false; // Input ignorato
    //     }
    //     // Registra l'input e aggiorna il tempo dell'ultimo input
    //     responses.push_back(Response(currentElapsed, std::string(1, static_cast<char>(ch))));
    //     lastResponseTime = currentElapsed;
    //     endwin();           // Termina ncurses
    //     return true;
    // }

    // endwin();
    return false;
}

void ResponseController::resetLastResponse()
{
    lastResponseTime = 0;  // Reset lastResponseTime per il nuovo trial
}

bool ResponseController::getPedalState(){ // check whther the pedl has been pressed or not and return 'true' asa it is pressed
    if(lgGpioRead(GC::GPIO,(int) 17)) return true;
    else return false;
}

bool ResponseController::fromJSON(string &jsonstring)
{
    rapidjson::Document doc;
    if(!GC::loadJSONFromString(doc,jsonstring)) {cout << "ERROR CONFIGURING RESPONSECONTROLLER from JSON\n"; return false;}
    else{cout << "Possible error: ResponseController JSON must doesn't specify KEYS array of strings to check\n";}
    return true;
}

string ResponseController::getResponsesJSONArray()
{
    string toreturn="[";
    for(auto& r : responses){
        toreturn+="{"+GC::qenc("TIME")+":"+to_string(r.timestamp)+","+GC::qenc("KEY")+":"+GC::qenc(std::string(r.side))+"}";
    }
    toreturn+="]";
    return toreturn;
}
