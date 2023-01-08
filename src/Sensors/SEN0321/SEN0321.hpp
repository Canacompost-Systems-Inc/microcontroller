#ifndef SEN0321_H
#define SEN0321_H

#include "Sensor.hpp"
#include <DFRobot_OzoneSensor.h>


class SEN0321: public Sensor {
 private:
  // Smoothing rate of data collection (range 1-100)
  static const int COLLECT_NUMBER = 20;

  // iic slave Address, The default is ADDRESS_3
  //    ADDRESS_0    0x70
  //    ADDRESS_1    0x71
  //    ADDRESS_2    0x72
  //    ADDRESS_3    0x73
  int baseAddress;
  DFRobot_OzoneSensor sen0321;

  Array<float> read();

 public:
  SEN0321(char inBaseDID, unsigned long inPollingFrequency, int inBaseAddress):
    Sensor(inBaseDID, inPollingFrequency), baseAddress(inBaseAddress), sen0321() {};

  void begin();
};

#endif