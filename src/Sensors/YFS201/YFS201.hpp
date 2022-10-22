#ifndef YFS201_H
#define YFS201_H

#include "Sensor.hpp"
#include "DFRobot_SHT40.h"


class YFS201: public Sensor {
 private:
  float pulseFrequency;
  Array<float> read();

 public:
  YFS201(char inBaseDID, unsigned long inPollingFrequency, int inPin):
    Sensor(inBaseDID, inPollingFrequency, inPin) {};

  void begin();
  void pulse();
};

#endif