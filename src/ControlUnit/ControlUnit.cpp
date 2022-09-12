#include "ControlUnit.hpp"


int ControlUnit::calculateArrayPositionFromDID(byte inDID)
{
    static int sensorIndexOffset = 192;
    static int actuatorIndexOffset = 224;
    int i_inDID = (int) inDID;

    if (i_inDID >= 192 && i_inDID <= 223)
    {
        // Sensor DID's range from 0xC0 to 0xDF, which is the ints 192 (sensor @ el 0) to 223 (sensor @ el 31)
        return (i_inDID - sensorIndexOffset);
    }
    else if (i_inDID >= 224 && i_inDID <= 255)
    {
        // Actuator DID's range from 0xE0 to 0xFF, which is the ints 224 (actuator @ el 0) 
        // to 255 (actuator @ el 31)
        return (i_inDID - actuatorIndexOffset);
    }
    else
    {
        return -1;
    }
}

void ControlUnit::executeGetSnapshot()
{
    for (int i = 0; i < sensors.getSize(); i++)
    {
        sensors.read(i)->report();
    }

    for (int j = 0; j < actuators.getSize(); j++)
    {
        actuators.read(j)->report();
    }
}

void ControlUnit::executeGetSensor()
{
    byte did = buffer[1];
    // int indexOffset = 192;
    // int arrayPosition = ((int) did) - indexOffset;
    int arrayPosition = calculateArrayPositionFromDID(did);

    if (arrayPosition >= 0 && arrayPosition < sensors.getSize())
    {
        sensors.read(arrayPosition)->report();
    }
    else
    {
        Serial.write(NAK);
    }
}

void ControlUnit::executeGetActuator()
{
    byte did = buffer[1];
    // int indexOffset = 224;
    // int arrayPosition = ((int) did) - indexOffset;
    int arrayPosition = calculateArrayPositionFromDID(did);

    if (arrayPosition >= 0 && arrayPosition < actuators.getSize())
    {
        actuators.read(arrayPosition)->report();
    }
    else
    {
        Serial.write(NAK);
    }
}

void ControlUnit::executeSetActuator()
{
    byte did = buffer[1];
    byte newState = buffer[2];
    // int indexOffset = 224;
    // int arrayPosition = ((int) did) - indexOffset;
    int arrayPosition = calculateArrayPositionFromDID(did);
    
    // Payload verification
    bool payloadIsConsistant = (newState == buffer[3] && newState == buffer[4] && newState == buffer[5]);
    bool positionInRange = (arrayPosition >= 0 && arrayPosition < actuators.getSize());

    if (payloadIsConsistant && positionInRange)
    {
        if (actuators.read(arrayPosition)->setState(newState) == true)
        {
            Serial.write(ACK);
        }
        else
        {
            Serial.write(NAK);
        }
    }
    else
    {
        Serial.write(NAK);
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

        case GET_ACTUATOR_OPCODE:
            executeGetActuator();
            break;

        case SET_ACTUATOR_OPCODE:
            executeSetActuator();
            break;

        default:
            Serial.write(NAK);
            break;
    }
    Serial.write(ETX);

    state = IDLE;
}

void ControlUnit::pollSensorsLoop()
{
    unsigned long currentTimeMs = millis();
	for (int i = 0; i < sensors.getSize(); i++)
	{
		sensors.read(i)->loop(currentTimeMs);
	}
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

ControlUnit::ControlUnit() 
{
    state = IDLE;
    buffer[MAX_BUFFER_SIZE] = { NULL };
    bufferCount = 0;
}

void ControlUnit::begin(Array<Actuator*> configuredActuators, Array<Sensor*> configuredSensors)
{
    actuators = configuredActuators;
    sensors = configuredSensors;
}

void ControlUnit::loop()
{
    transceiverLoop();
    pollSensorsLoop();
}