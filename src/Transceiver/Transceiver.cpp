#include "Transceiver.hpp"

Transceiver::Transceiver() 
{
    state = IDLE;
    buffer[MAX_BUFFER_SIZE] = { NULL };
    bufferCount = 0;
    opcode = NULL;
    did = NULL;
    payload[MAX_PAYLOAD_SIZE] = { NULL };
}

void Transceiver::loop()
{
    if (!Serial.available()) return;

    byte inByte = Serial.read();
    switch(state) 
    {
        case IDLE:
            if (inByte == STX)
            {
                state = DECODE;
            }

        case FETCH:
            if (bufferCount < MAX_BUFFER_SIZE)
            {
                buffer[bufferCount] = inByte;
                bufferCount++;
            }
            else
            {
                state = DECODE;
                bufferCount = 0;
            }

        case DECODE:
            opcode = buffer[0];
            did = buffer[1];
            for (int i = 0; i < MAX_PAYLOAD_SIZE; i++)
            {
                payload[i] = buffer[i+2];
            }

            state = EXECUTE;

        case EXECUTE:
            state = IDLE;

        default:
            state = IDLE;
    }   
}