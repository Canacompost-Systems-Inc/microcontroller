#ifndef SHT40_H
#define SHT40_H

#include "Sensor.hpp"
#include "DFRobot_SHT40.h"


class SHT40: public Sensor 
{    
    private:
        DFRobot_SHT40 sht40;
        Array<float> read();

    public:
        SHT40(String inName, unsigned long inPollingFrequency, int inPin):
            Sensor(inName, inPollingFrequency, inPin), sht40(SHT40_AD1B_IIC_ADDR) {};

        void begin();
};

#endif