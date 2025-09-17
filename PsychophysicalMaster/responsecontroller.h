#ifndef RESPONSECONTROLLER_H
#define RESPONSECONTROLLER_H

#include <list>
#include <vector>
#include <string>
#include <chrono>


using namespace std;

struct Response{
    Response(long _timestamp, const char* _side) : timestamp(_timestamp), side(_side){}
    long timestamp;
    const char* side;
};

class ResponseController
{
public:
    ResponseController();



    void reset();
    void resetLastResponse();

    void init_keyboard(const char *device_path, struct libevdev **dev);
    void start(std::chrono::high_resolution_clock::time_point _start);
    bool processEvents(std::chrono::system_clock::time_point this_time, struct libevdev *dev);
    bool getPedalState();



    bool fromJSON(string& jsonstring);
    string getResponsesJSONArray();

    std::chrono::high_resolution_clock::time_point start_time;

    // bool keydown=false;
    list<Response> responses;

    std::vector<int> keyboard_side_L;
    std::vector<int> keyboard_side_R;

    void clear_stdin();
    private:
    bool pedal_state;
    long lastResponseTime;  // Tempo dell'ultima risposta
    static const long DEBOUNCE_INTERVAL = 200; // Intervallo di debounce (200 ms)


};

#endif // RESPONSECONTROLLER_H
