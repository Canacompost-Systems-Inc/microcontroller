#ifndef SEN0441_H
#define SEN0441_H

#include "Sensor.hpp"
#include <DFRobot_MICS.h>
#include <Arduino.h>

class SEN0441: public Sensor {
 public:
  SEN0441(char inBaseDID, unsigned long inPollingFrequency, int inSignalPin, bool inNeedsCalibration):
    Sensor(inBaseDID, inPollingFrequency), sen0441(A0, inSignalPin), needsCalibration(inNeedsCalibration) {};

  void begin();
  
  /**
   * Runs calibration. Sensor must be in clean air enviornment (different environment than it reads from).
   * Do not touch the sensor probe when preheating the sensor. Calibrates for CALIBRATION_TIME.
   */
  void calibrate();

 private:
  static const int CALIBRATION_TIME = 3;

  DFRobot_MICS_ADC sen0441;
  bool needsCalibration;

  Array<float> read();
};

#endif