#ifndef MQSENSOR_H
#define MQSENSOR_H

#include "Sensor.hpp"


class MQSensor: public Sensor 
{
    // Inherit base constructor
    using Sensor::Sensor;

    private:
        int read();
};

#endif