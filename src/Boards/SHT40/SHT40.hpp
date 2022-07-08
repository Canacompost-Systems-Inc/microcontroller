#ifndef SHT40_H
#define SHT40_H

#include "Sensor.hpp"
#include "DFRobot_SHT40.h"


class SHT40: public Sensor 
{    
    private:
        DFRobot_SHT40 sht40;
        virtual void read();

    public:
        SHT40(String inName, int inPin, unsigned long inPollingFrequency):
            Sensor(inName, inPin, inPollingFrequency), sht40(SHT40_AD1B_IIC_ADDR) {};

        void begin();
};

#endif