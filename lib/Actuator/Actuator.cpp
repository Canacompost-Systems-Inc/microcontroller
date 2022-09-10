#include "Actuator.hpp"

Actuator::Actuator(char inDid, int inPin)
{
    did = inDid;
    pin = inPin;
}

void Actuator::begin()
{
    setState(B_LOW);
}

void Actuator::report()
{
    Serial.write(did);

    for (int i = 0; i < 4; i++)
    {
        Serial.write(state);
    }
}

bool Actuator::setState(byte newState)
{
    if (newState == B_HIGH)
    {
        state = B_HIGH;
        digitalWrite(pin, HIGH);
        return true;    
    }
    else if (newState == B_LOW)
    {
        state = B_LOW;
        digitalWrite(pin, LOW);
        return true;    
    }
    else
    {
        return false;
    }
}