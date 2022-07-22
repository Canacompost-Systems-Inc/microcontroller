#include "Sensor.hpp"


Sensor::Sensor(String inName, unsigned long inPollingFrequency, int inPin)
{
    state = IDLE;
    dataTimestamp = 0;
    name = inName;
    pollingFrequency = inPollingFrequency;
    pin = inPin;

    Array<float> emptyData;
    data = emptyData;
}

void Sensor::debugReport()
{
    Serial.print("\n");
    Serial.print(name);
    Serial.print(" [");
    Serial.print(dataTimestamp);
    Serial.print("]: ");

    for(int i = 0; i < data.getSize(); i++)
    {
        Serial.print(data.read(i));
        Serial.print(' ');
    }
}

void Sensor::FSM(unsigned long currentTimestamp)
{ 
    switch(state) 
    {
        case IDLE:
            if(currentTimestamp - dataTimestamp >= pollingFrequency)
            {
                // Take reading once polling interval elapsed
                state = READING;
                data = read();
                dataTimestamp = currentTimestamp;
                debugReport();
            } 

        case READING:
            // Sensor reading done
            state = IDLE;

        default:
            state = IDLE;
    }
}

unsigned long Sensor::getPollingFrequency()
{
    return pollingFrequency;
}

int Sensor::getPin()
{
    return pin;
}

void Sensor::setPollingFrequency(unsigned long newPollingFrequency)
{
    pollingFrequency = newPollingFrequency;
}