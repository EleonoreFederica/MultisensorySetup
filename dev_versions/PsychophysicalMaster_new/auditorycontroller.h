#ifndef AUDITORYCONTROLLER_H
#define AUDITORYCONTROLLER_H

#include "gc.h"
#include "auditory_stimulus.h"

class AuditoryController
{
public:
    AuditoryController();

    void update(long time,vector<Auditory_Stimulus>& astim);
};

#endif // AUDITORYCONTROLLER_H
