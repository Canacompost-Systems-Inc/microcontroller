#ifndef SENSOR_H
#define SENSOR_H


enum State { IDLE, READING };

class Sensor
{
    protected:
        State state;
        int pin;
        int data;
        unsigned long dataTimestamp;
        unsigned long pollingInterval;

        // Inheriting class must override the read() virtual function and implement the logic for reading 
        // from sensor. If no override is present will return current value of data. 
        virtual int read() { return data; };

    public:
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