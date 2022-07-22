#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Array.hpp"

const int DATA_ARRAY_SIZE = 4;
enum State { IDLE, READING };

class Sensor
{
    private:
        State state;
        String name;
        Array<float> data;
        unsigned long dataTimestamp;
        unsigned long pollingFrequency;
        int pin;

        /**
         * Used to print data to serial monitor when debugging.
         */ 
        void debugReport();


    protected:
        /**
         * Inheriting class should override the read() virtual function and implement the logic for reading 
         * from sensor. If no override is present will return current value of data. 
         */ 
        virtual Array<float> read() { return data; };

    public:

        /**
         * @param inName used for identifying sensor when debugging
         * @param inPollingFrequency number of milliseconds between data samples
         * @param inPin GPIO pin connected to the board 
         */ 
        Sensor(String inName, unsigned long inPollingFrequency, int inPin);

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

        int getPin();

        /**
         * @param newPollingFrequency milliseconds of new desired frequency
         */ 
        void setPollingFrequency(unsigned long newPollingFrequency);
};

#endif