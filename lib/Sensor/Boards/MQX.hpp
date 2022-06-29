#ifndef MQX_H
#define MQX_H

#include "Sensor.hpp"


class MQX: public Sensor 
{
    // Inherit base constructor
    using Sensor::Sensor;

    private:
        float read();
};

#endif