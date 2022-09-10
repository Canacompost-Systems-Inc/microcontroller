#include <Arduino.h>
#include "Array.hpp"
#include "Sensor.hpp"
#include "Actuator.hpp"
#include "Boards/SHT40/SHT40.hpp"
#include "Boards/SCD41/SCD41.hpp"

class ControlUnit
{
    private:
        // Sizing Constants
        static const int MAX_PAYLOAD_SIZE = 4;
        static const int MAX_BUFFER_SIZE = 6;

        // Control Characters
        static const byte STX = 0x01;
        static const byte ETX = 0x03;
        static const byte ACK = 0x06;
        static const byte NAK = 0x15;

        // Opcodes
        static const byte GET_SNAPSHOT_OPCODE = 0xA0;
        static const byte GET_SENSOR_OPCODE = 0xA1;
        static const byte GET_ACTUATOR_OPCODE = 0xA2;
        static const byte SET_ACTUATOR_OPCODE = 0xB0;

        enum State { IDLE, FETCH, EXECUTE };
        
        Array<Actuator*> actuators;
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
        void executeGetActuator();
        void executeSetActuator();
        void executeHandler();

    public:
        ControlUnit();

        /**
         * sets array of actuators and sensors to values passed into constructor
         * 
         * @param configuredActuators array of Actuator objects
         * @param configuredSensors array of Sensor objects
         */ 
        void begin(Array<Actuator*> configuredActuators, Array<Sensor*> configuredSensors);

        /**
         * Main loop of control unit, called ever clock cycle. Polls sensors and handles transmissions from
         */
        void loop();
};