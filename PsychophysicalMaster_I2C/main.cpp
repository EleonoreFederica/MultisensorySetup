#include <iostream>

#include <asio.hpp>
#include "gc.h"
// #include "ncurses.h"



#include "experiment.h"


using namespace std;
using asio::ip::tcp;

volatile bool interrupt_received=false;

GC gc;


static void InterruptHandler(int signo) { interrupt_received=true;}





int main()
{
    signal(SIGTERM,InterruptHandler);
    signal(SIGINT,InterruptHandler);

    int IN =20;
    int OUT1=21;
    int OUT2=22;
    int ALERT=23;


    // initscr();
    // cbreak();
    // noecho();
    // nodelay(stdscr,TRUE);
    // scrollok(stdscr,TRUE);



    cout << "\rLoading config.json...";
    GC::loadConfig("config.json");
    cout << "...done\n";


    // int old_v, v;
    // int lFlags = 0; /* default line flags */

    // /* get a handle to the GPIO */
    // // h = lgGpiochipOpen(0);

    // /* claim a GPIO for INPUT */
    // lgGpioClaimInput(GC::GPIO, lFlags, IN);

    // /* claim some GPIO for OUTPUT */
    // lgGpioClaimOutput(GC::GPIO, lFlags, OUT1, 0); /* initial level 0 */
    // lgGpioClaimOutput(GC::GPIO, lFlags, OUT2, 1); /* initial level 1 */

    // /* claim a GPIO for ALERTS */
    // lgGpioClaimAlert(GC::GPIO, lFlags, LG_BOTH_EDGES, ALERT, -1);

    // /* set up a callback for the alerts */
    // lgGpioSetAlertsFunc(GC::GPIO, ALERT, GC::cbf, NULL);

    // /* output 1000 cycles of PWM: frequency=20 dutycycle=35 */
    // lgTxPwm(GC::GPIO, OUT2, 20.0, 35.0, 0, 1000);

    // old_v =-1;

    // while (1)
    // {
    //     v = lgGpioRead(GC::GPIO, IN);
    //     if (v != old_v)
    //     {
    //         lgGpioWrite(GC::GPIO, OUT1, v);
    //         printf("GPIO %d now %d\n", OUT1, v);
    //         old_v = v;
    //     }
    //     lguSleep(0.1); /* sleep for 0.1 seconds */
    // }



    Experiment exp;
    cout << "=== START EXP ===\n";
    string expjson = GC::getJSONStringFromFile("sample_experiment.json");
    exp.fromJSON(expjson);
    exp.runExperiment();

    cout << "\rComplete!" << endl;
    return 0;
}
