#include "auditorycontroller.h"
#include <iostream>

AuditoryController::AuditoryController() {}

void AuditoryController::update(long time, vector<Auditory_Stimulus> &astim)
{
    for(auto& as : astim){
        if(as.state==Auditory_Stimulus::DURING){
            if(time>as.offset){
                as.state=Auditory_Stimulus::PRE;
            }
        }
        else if((time>as.onset)&&(time<as.offset)){
            if(as.state==Auditory_Stimulus::PRE){
                as.state=Auditory_Stimulus::DURING;
                // int randomValue = rand() % 2;
                // lgGpioWrite(GC::GPIO,as.channel,randomValue);
                lgTxPwm(GC::GPIO,as.channel,as.frequency,as.duty_cycle,as.cycle_offset,as.frequency*(float)(as.offset-as.onset)/1000.f);
            }

            // as.cleared=true;
            // }

            // handle,
            // gpio,
            // pwmFrequency,
            // pwmDutyCycle,
            // pwmOffset,
            // pwmCycles
        }

    }
    // for(auto& as : astim){
    //     if(time>=as.offset){
    //          if(!as.cleared){
    //             as.cleared=true;
    //             lgGpioWrite(GC::GPIO,as.channel,0);
    //             // std::cout << "clear";
    //          }
    //     }
    //     else if((time>as.onset)){
    //         if(as.cleared==true) as.cleared=false;
    //         // std::cout << "play";

    //         // if(!as.cleared){
    //             lgTxPwm(GC::GPIO,as.channel,as.frequency,as.duty_cycle,as.offset,as.cycle_offset);
    //             // as.cleared=true;
    //         // }

    //        // handle,
    //        // gpio,
    //        // pwmFrequency,
    //        // pwmDutyCycle,
    //        // pwmOffset,
    //        // pwmCycles
    //     }

    // }
}
