#include "ControlUnit.hpp"


ControlUnit::ControlUnit() 
{
    state = IDLE;
    buffer[MAX_BUFFER_SIZE] = { NULL };
    bufferCount = 0;
}

void ControlUnit::pollSensorsLoop()
{
    unsigned long currentTimeMs = millis();
	for (int i = 0; i < sensors.getSize(); i++)
	{
		sensors.read(i)->loop(currentTimeMs);
	}
}

void ControlUnit::idleHandler()
{
    if (Serial.available())
    {
        byte inByte = Serial.read();

        if (inByte == STX)
        {
            state = FETCH;
        }
    }
}

void ControlUnit::fetchHandler()
{
    if (Serial.available()) 
    {
        byte inByte = Serial.read();

        if (bufferCount == MAX_BUFFER_SIZE)
        {
            bufferCount = 0;

            if (inByte == ETX)
            {
                state = EXECUTE;
            }
            else
            {
                Serial.write(STX);
                Serial.write(NAK);
                Serial.write(ETX);
                state = IDLE;
            }
        }
        else
        {
            buffer[bufferCount] = inByte;
            bufferCount++;
        }
    }
}

void ControlUnit::executeGetSnapshot()
{
    for (int i = 0; i < sensors.getSize(); i++)
    {
        sensors.read(i)->report();
    }
}

void ControlUnit::executeGetSensor()
{
    byte did = buffer[1];
    int indexOffset = 192;
    int arrayPosition = ((int) did) - indexOffset;

    if (arrayPosition >= 0 && arrayPosition < sensors.getSize())
    {
        sensors.read(arrayPosition)->report();
    }
    else
    {
        Serial.write(NAK);
    }
}

void ControlUnit::executeHandler()
{ 
    byte opcode = buffer[0];

    Serial.write(STX);
    switch (opcode)
    {

        case GET_SNAPSHOT_OPCODE:
            executeGetSnapshot();
            break;
        
        case GET_SENSOR_OPCODE:
            executeGetSensor();
            break;

        default:
            Serial.write(NAK);
            break;
    }
    Serial.write(ETX);

    state = IDLE;
}

void ControlUnit::transceiverLoop()
{
    switch (state)
    {
        case IDLE:
            idleHandler();
            break;
        
        case FETCH:
            fetchHandler();
            break;

        case EXECUTE:
            executeHandler();
            break;
            
        default:
            break;
    }
}

void ControlUnit::begin(Array<Sensor*> configuredSensors)
{
    sensors = configuredSensors;
}

void ControlUnit::loop()
{
    transceiverLoop();
    pollSensorsLoop();
}