#include "flighttime.h"

flighttime::flighttime(QObject *parent) :
    QThread(parent)
{
}

void flighttime::run()
{
    uint32_t time;
    while(1)
    {
        sleep(1);
        emit onUpdateFlightTime(time++);
    }
}
