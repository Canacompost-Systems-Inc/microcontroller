#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>


enum State { IDLE, READING };

class Sensor
{
    protected:
        State state;
        int pin;
        float data;
        unsigned long dataTimestamp;
        unsigned long pollingInterval;

        // Inheriting class must override the read() virtual function and implement the logic for reading 
        // from sensor. If no override is present will return current value of data. 
        virtual float read() { return data; };

    public:
        Sensor(unsigned long initialPollingInterval);
        Sensor(int initialPin, unsigned long initialPollingInterval);
        void FSM(unsigned long currentTimestamp);

        // Getters
        int getPin();
        unsigned long getPollingInterval();

        // Setters
        void setPin(int newPin);
        void setPollingInterval(unsigned long newPollingInterval);
};

#endif