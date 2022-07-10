#ifndef IPC101xx_H
#define IPC101xx_H

#include "Sensor.hpp"
#include <icp101xx.h>


class IPC101xx: public Sensor 
{
    private:
        ICP101xx ipc101xx;
        void read();

    public:
        IPC101xx(String inName, int inPin, unsigned long inPollingFrequency, bool inEnabled):
            Sensor(inName, inPin, inPollingFrequency, inEnabled) {};

        void begin();
};

#endif