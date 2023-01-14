#ifndef SCD41_H
#define SCD41_H

#include "Sensor.hpp"
#include <Wire.h>
#include <SensirionI2CScd4x.h>

class SCD41: public Sensor {
 public:
  SCD41(char inBaseDID, unsigned long inPollingFrequency):
    Sensor(inBaseDID, inPollingFrequency) {};

  void begin();

 private:
  Array<float> read();

  SensirionI2CScd4x scd41;
};

#endif