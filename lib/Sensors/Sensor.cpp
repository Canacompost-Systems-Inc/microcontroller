#include "Sensor.hpp"
#include "Arduino.h"


Sensor::Sensor(int initialPin, unsigned long initialPollingInterval)
{
    state = IDLE;
    pin = initialPin;
    data = -1;
    pollingInterval = initialPollingInterval;
    dataTimestamp = 0;
};

void Sensor::FSM(unsigned long currentTimestamp)
{ 
    switch(state) 
    {
        case IDLE:
            if(currentTimestamp - dataTimestamp >= pollingInterval)
            {
                // Take reading once polling interval elapsed
                state = READING;
                data = read();
                dataTimestamp = currentTimestamp; 

                // DEBUG ---
                Serial.print(pin);
                Serial.print(": ");
                Serial.print(data);
                Serial.print(" ");
                Serial.println(dataTimestamp);
                // --- DEBUG
            } 

        case READING:
            // Sensor reading done
            state = IDLE;

        default:
            state = IDLE;
    }
};