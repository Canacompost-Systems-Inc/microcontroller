#ifndef SEN0441_H
#define SEN0441_H

#include "Sensor.hpp"
#include <DFRobot_MICS.h>
#include <Arduino.h>

// TODO: Remove after confirm 
// #define ADC_PIN   A0
// #define POWER_PIN 10

class SEN0441: public Sensor {
 private:
  static const int CALIBRATION_TIME = 3;
  DFRobot_MICS_ADC sen0441;
  Array<float> read();

 public:
  SEN0441(char inBaseDID, unsigned long inPollingFrequency, int inPin):
    Sensor(inBaseDID, inPollingFrequency, inPin), sen0441(A0, inPin)  {};

  void begin();
};

#endif