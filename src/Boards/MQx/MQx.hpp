#ifndef MQX_H
#define MQX_H

#include "Sensor.hpp"


class MQx: public Sensor 
{
    private:
        void read();

    public:
        MQx(String inName, int inPin, unsigned long inPollingFrequency, bool inEnabled):
            Sensor(inName, inPin, inPollingFrequency, inEnabled) {};
};

#endif