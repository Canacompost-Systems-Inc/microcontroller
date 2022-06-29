#include "MQX.hpp"


float MQX::read()
{
    return analogRead(pin);
}