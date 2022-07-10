#include "Sensor.hpp"


Sensor::Sensor(String inName, int inPin, unsigned long inPollingFrequency, bool inEnabled)
{
    state = IDLE;
    enabled = inEnabled;
    pollingFrequency = inPollingFrequency;
    dataTimestamp = 0;
    pin = inPin;
    name = inName;

    clearData();
}

void Sensor::debugReport()
{
    Serial.print("\n");
    Serial.print(name);
    Serial.print(" [");
    Serial.print(dataTimestamp);
    Serial.print("]: ");

    for(int i; i < DATA_ARRAY_SIZE; i++)
    {
        if (valid[i])
        {
            Serial.print(data[i]);
            Serial.print(' ');
        }
    }
}

void Sensor::clearData()
{
    for (int i; i < DATA_ARRAY_SIZE; i++)
    {
        data[i] = 0;
        valid[i] = false;
    }
}

void Sensor::FSM(unsigned long currentTimestamp)
{ 
    if (enabled)
    {
        switch(state) 
        {
            case IDLE:
                if(currentTimestamp - dataTimestamp >= pollingFrequency)
                {
                    // Take reading once polling interval elapsed
                    state = READING;
                    read();
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
}

unsigned long Sensor::getPollingFrequency()
{
    return pollingFrequency;
}

void Sensor::setPollingFrequency(unsigned long newPollingFrequency)
{
    pollingFrequency = newPollingFrequency;
}