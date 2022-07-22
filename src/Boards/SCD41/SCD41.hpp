#ifndef SCD41_H
#define SCD41_H

#include "Sensor.hpp"
#include <Wire.h>
#include <SensirionI2CScd4x.h>


class SCD41: public Sensor 
{
    private:
        SensirionI2CScd4x scd41;
        Array<float> read();

    public:
        SCD41(String inName, unsigned long inPollingFrequency, int inPin):
            Sensor(inName, inPollingFrequency, inPin) {};

        void begin();
};

#endif