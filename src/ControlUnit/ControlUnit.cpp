#include "ControlUnit.hpp"

ControlUnit::ControlUnit() 
{
    state = IDLE;
    buffer[MAX_BUFFER_SIZE] = { NULL };
    bufferCount = 0;
    opcode = NULL;
    did = NULL;
    payload[MAX_PAYLOAD_SIZE] = { NULL };
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
                state = DECODE;
            }
            else
            {
                Serial.write(NAK);
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

void ControlUnit::decodeHandler()
{
    opcode = buffer[0];
    did = buffer[1];

    for (int i=0; i < MAX_PAYLOAD_SIZE; i++)
    {
        payload[i] = (buffer[i]+2);
    }

    state = EXECUTE;
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
    int arrayPosition = int(did) - 127;

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
    switch (opcode)
    {
        case 0xFF:
            Serial.write(STX);
            executeGetSnapshot();
            Serial.write(ETX);
            break;
        
        case 0xFE:
            Serial.write(STX);
            executeGetSensor();
            Serial.write(ETX);
            break;

        default:
            Serial.write(NAK);
            break;
    }

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

        case DECODE:
            decodeHandler();
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
    pollSensorsLoop();
    transceiverLoop();
}