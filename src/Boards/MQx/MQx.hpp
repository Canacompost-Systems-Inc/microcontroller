#ifndef MQX_H
#define MQX_H

#include "Sensor.hpp"


class MQx: public Sensor 
{
    private:
        Array<float> read();

    public:
        MQx(String inName, unsigned long inPollingFrequency, int inPin):
            Sensor(inName, inPollingFrequency, inPin) {};
};

#endif