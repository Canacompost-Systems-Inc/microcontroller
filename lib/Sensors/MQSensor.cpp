#include <Arduino.h>
#include "MQSensor.hpp"


int MQSensor::read()
{
    return analogRead(pin);
}