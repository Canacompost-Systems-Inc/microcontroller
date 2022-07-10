#ifndef DS18B20_H
#define DS18B20_H

#include "Sensor.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>


class DS18B20: public Sensor 
{
    private:
        OneWire oneWire;	
        DallasTemperature ds18b20;
        void read();

    public:
        DS18B20(String inName, int inPin, unsigned long inPollingFrequency, bool inEnabled):
            Sensor(inName, inPin, inPollingFrequency, inEnabled), oneWire(inPin), ds18b20(&oneWire) {};

        void begin();
};

#endif