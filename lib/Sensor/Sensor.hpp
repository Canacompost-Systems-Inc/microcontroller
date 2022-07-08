#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>


const int DATA_ARRAY_SIZE = 4;
enum State { IDLE, READING };

class Sensor
{
    protected:
        String name;
        State state;
        float data[DATA_ARRAY_SIZE];
        bool valid[DATA_ARRAY_SIZE];
        unsigned long dataTimestamp;
        unsigned long pollingFrequency;
        int pin;
        int mode;

        /**
         * Inheriting class should override the read() virtual function and implement the logic for reading 
         * from sensor. If no override is present will return current value of data. 
         */ 
        virtual void read() {};

        /**
         * Used to print data to serial monitor when debugging.
         */ 
        void debugReport();

        /**
         * Will set all elements in data will to 0; and  all elements in valid to false
         */ 
        void clearData();

    public:

        /**
         * @param inName used for identifying sensor when debugging
         * @param inPin GPIO pin connected to the board 
         * @param inPollingFrequency number of milliseconds between data samples  
         */ 
        Sensor(String inName, int inPin, unsigned long inPollingFrequency);

        /**
         * Inheriting class can override the begin() virtual function and implement any setup logic needed 
         * for sensor. If no override is present this function will do nothing.
         */ 
        virtual void begin() {};

        /**
         * Runs Sensor Finite State Machine (FSM), controls when to take readings from sensor based on the
         * desired pollingFrequency.
         * 
         * @param currentTimestamp arduino timestamp returned from the function millis()
         */ 
        void FSM(unsigned long currentTimestamp);

        /**
         * @return current value for pollingFrequency
         */ 
        unsigned long getPollingFrequency();

        /**
         * @param newPollingFrequency milliseconds of new desired frequency
         */ 
        void setPollingFrequency(unsigned long newPollingFrequency);
};

#endif