#ifndef SENSOR_H
#define SENSOR_H


enum State { IDLE, READING };

class Sensor
{
    protected:
        // Member Varibales
        State state;
        int pin;
        int data;
        unsigned long dataTimestamp;
        unsigned long pollingInterval;

        // Private helper functions
        virtual int read() { return data; };

    public:
        Sensor(int initialPin, unsigned long initialPollingInterval);
        void FSM(unsigned long currentTimestamp);

        // Getters
        int getPin();
        unsigned long getPollingInterval();

        // Setters
        bool setPin();
        bool setPollingInterval();
};

#endif