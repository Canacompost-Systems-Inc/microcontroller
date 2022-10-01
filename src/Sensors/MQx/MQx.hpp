#ifndef MQX_H
#define MQX_H

#include "Sensor.hpp"


class MQx: public Sensor {
 private:
  Array<float> read();

 public:
  MQx(char inBaseDID, unsigned long inPollingFrequency, int inPin):
    Sensor(inBaseDID, inPollingFrequency, inPin) {};
};

#endif