#ifndef SHT40_H
#define SHT40_H

#include "Sensor.hpp"
#include "DFRobot_SHT40.h"


enum Mode { TEMP, HUM };

class SHT40: public Sensor 
{
    private:
        DFRobot_SHT40 sht40;
        Mode mode;

        float read();

    public:
        SHT40(Mode initialMode, unsigned long initialPollingInterval);
        void begin();
};

#endif