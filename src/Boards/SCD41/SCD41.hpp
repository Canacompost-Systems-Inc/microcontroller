#ifndef SCD41_H
#define SCD41_H

#include "Sensor.hpp"
#include <Wire.h>
#include <SensirionI2CScd4x.h>


class SCD41: public Sensor 
{
    private:
        SensirionI2CScd4x scd41;
        void read();

    public:
        SCD41(String inName, int inPin, unsigned long inPollingFrequency, bool inEnabled):
            Sensor(inName, inPin, inPollingFrequency, inEnabled) {};

        void begin();
};

#endif