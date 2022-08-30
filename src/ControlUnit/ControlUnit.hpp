#include <Arduino.h>
#include "Array.hpp"
#include "Sensor.hpp"
#include "Boards/SHT40/SHT40.hpp"
#include "Boards/SCD41/SCD41.hpp"

class ControlUnit
{
    private:
        static const int MAX_PAYLOAD_SIZE = 4;
        static const int MAX_BUFFER_SIZE = 6;
        static const byte STX = 0x01;
        static const byte ETX = 0x03;
        static const byte NAK = 0x15;

        enum State { IDLE, FETCH, DECODE, EXECUTE };
        
        Array<Sensor*> sensors;

        State state;
        byte buffer[MAX_BUFFER_SIZE];
        int bufferCount;
        byte opcode;
        byte did;
        byte payload[MAX_PAYLOAD_SIZE];

        void pollSensorsLoop();
        void transceiverLoop();

        void idleHandler();
        void fetchHandler();
        void decodeHandler();

        void executeGetSnapshot();
        void executeGetSensor();
        void executeHandler();

    public:
        ControlUnit();
        void begin(Array<Sensor*> configuredSensors);
        void loop();
};