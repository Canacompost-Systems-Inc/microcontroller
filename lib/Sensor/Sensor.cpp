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

void Sensor::report()
{
    for(int i = 0; i < data.getSize(); i++)
    {
        float dataToWrite = data.read(i);
        const unsigned char *bytesPtr = reinterpret_cast<const unsigned char*>(&dataToWrite);

        // Write out transmission block
        Serial.write(0x02); // STX: Start of text
        Serial.write(baseDID + i); // DID: Device ID
        for(size_t j = 0; j != sizeof(float); j++)
        {
            Serial.write(bytesPtr[j]); // DATA
        }
        Serial.write(0x03); // ETX: End of text
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
                report();
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