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

        static const byte GET_SNAPSHOT_OPCODE = 0xA0;
        static const byte GET_SENSOR_OPCODE = 0xA1;
        static const byte GET_ACTUATOR_OPCODE = 0xA2;
        static const byte SET_SENSOR_OPCODE = 0xC0;
        static const byte SET_ACTUATOR_OPCODE = 0xC1;

        enum State { IDLE, FETCH, EXECUTE };
        
        Array<Sensor*> sensors;
        State state;
        byte buffer[MAX_BUFFER_SIZE];
        int bufferCount;

        void pollSensorsLoop();
        void transceiverLoop();

        void idleHandler();
        void fetchHandler();

        void executeGetSnapshot();
        void executeGetSensor();
        void executeHandler();

    public:
        ControlUnit();
        void begin(Array<Sensor*> configuredSensors);
        void loop();
};