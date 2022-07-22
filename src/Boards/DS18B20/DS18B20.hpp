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
        Array<float> read();

    public:
        DS18B20(String inName, unsigned long inPollingFrequency, int inPin):
            Sensor(inName, inPollingFrequency, inPin), oneWire(inPin), ds18b20(&oneWire) {};

        void begin();
};

#endif