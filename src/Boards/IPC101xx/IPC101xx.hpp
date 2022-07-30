#ifndef IPC101xx_H
#define IPC101xx_H

#include "Sensor.hpp"
#include <icp101xx.h>


class IPC101xx: public Sensor 
{
    private:
        ICP101xx ipc101xx;
        Array<float> read();

    public:
        IPC101xx(char inBaseDID, unsigned long inPollingFrequency, int inPin):
            Sensor(inBaseDID, inPollingFrequency,  inPin) {};

        void begin();
};

#endif