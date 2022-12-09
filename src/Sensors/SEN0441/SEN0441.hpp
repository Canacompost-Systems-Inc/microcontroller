#ifndef SEN0441_H
#define SEN0441_H

#include "Sensor.hpp"
#include <DFRobot_MICS.h>
#include <Arduino.h>


class SEN0441: public Sensor {
 private:
  static const int CALIBRATION_TIME = 3;
  DFRobot_MICS_ADC sen0441;
  Array<float> read();

 public:
  SEN0441(char inBaseDID, unsigned long inPollingFrequency, int inSignalPin):
    Sensor(inBaseDID, inPollingFrequency), sen0441(A0, inSignalPin)  {};

  void begin();
};

#endif