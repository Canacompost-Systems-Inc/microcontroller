#include "Sensor.hpp"


Sensor::Sensor(char inBaseDID, unsigned long inPollingFrequency, int inPin)
{
    state = IDLE;
    dataTimestamp = 0;
    baseDID = inBaseDID;
    pollingFrequency = inPollingFrequency;
    pin = inPin;

    Array<float> emptyData;
    data = emptyData;
}

void Sensor::debugReport()
{
    Serial.print("\n");
    Serial.print(baseDID);
    Serial.print(" [");
    Serial.print(dataTimestamp);
    Serial.print("]: ");

    for(int i = 0; i < data.getSize(); i++)
    {
        Serial.print(data.read(i));
        Serial.print(' ');
    }
}

void Sensor::report()
{
    Serial.write(baseDID); // DID: Device ID

    // Send float value DATA_ARRAY_SIZE number of times
    for(int i = 0; i < DATA_ARRAY_SIZE; i++)
    {
        float dataToWrite = 0.0;

        // If sensor stores less data the DATA_ARRAY_SIZE zero pad transmission
        if (i < data.getSize())
        {
            dataToWrite = data.read(i);
        }

        // Convert float to bytes
        const unsigned char *bytesPtr = reinterpret_cast<const unsigned char*>(&dataToWrite);
        
        // Write out transmission block
        for(size_t j = 0; j != sizeof(float); j++)
        {
            Serial.write(bytesPtr[j]); 
        }
    }
}

void Sensor::loop(unsigned long currentTimestamp)
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