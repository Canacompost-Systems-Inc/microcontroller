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
        SCD41(char inBaseDID, unsigned long inPollingFrequency, int inPin):
            Sensor(inBaseDID, inPollingFrequency, inPin) {};

        void begin();
};

#endif