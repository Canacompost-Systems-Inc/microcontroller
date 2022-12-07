#ifndef YFS201_H
#define YFS201_H

#include "Sensor.hpp"
#include "DFRobot_SHT40.h"


class YFS201: public Sensor {
 private:
  float pulseFrequency;
  Array<float> read();
  int signalPin;

 public:
  YFS201(char inBaseDID, unsigned long inPollingFrequency, int inSignalPin):
    Sensor(inBaseDID, inPollingFrequency), signalPin(inSignalPin) {};

  void begin();
  void pulse();
  int getSignalPin() { return signalPin; }
};

#endif