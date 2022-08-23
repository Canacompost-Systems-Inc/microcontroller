#include <Arduino.h>

const int MAX_PAYLOAD_SIZE = 4;
const int MAX_BUFFER_SIZE = 6;
const byte STX = 0x01;

enum State { IDLE, FETCH, DECODE, EXECUTE };

class Transceiver
{
    private:
        State state;
        byte buffer[MAX_BUFFER_SIZE];
        int bufferCount;
        byte opcode;
        byte did;
        byte payload[MAX_PAYLOAD_SIZE];

    public:
        Transceiver();
        void loop();
};