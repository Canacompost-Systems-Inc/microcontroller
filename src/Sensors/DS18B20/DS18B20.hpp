#ifndef DS18B20_H
#define DS18B20_H

#include "Sensor.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20: public Sensor {
 public:
  DS18B20(char inBaseDID, unsigned long inPollingFrequency, int inSignalPin):
    Sensor(inBaseDID, inPollingFrequency), oneWire(inSignalPin), ds18b20(&oneWire) {};

  void begin();

 private:
  Array<float> read();
  
  OneWire oneWire;	
  DallasTemperature ds18b20;
};

#endif