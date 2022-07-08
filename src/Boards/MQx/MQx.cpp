#include "MQx.hpp"


void MQx::read()
{
    clearData();
    data[0] = analogRead(pin);
    valid[0] = true;
}