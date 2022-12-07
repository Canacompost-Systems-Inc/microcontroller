#ifndef MQX_H
#define MQX_H

#include "Sensor.hpp"


class MQx: public Sensor {
 private:
  Array<float> read();
  int analogSignalPin;

 public:
  MQx(char inBaseDID, unsigned long inPollingFrequency, int inAnalogSignalPin):
    Sensor(inBaseDID, inPollingFrequency), analogSignalPin(inAnalogSignalPin) {};
};

#endif