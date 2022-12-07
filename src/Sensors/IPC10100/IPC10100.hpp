#ifndef IPC101xx_H
#define IPC101xx_H

#include "Sensor.hpp"
#include <icp101xx.h>


class IPC10100: public Sensor {
 private:
  ICP101xx ipc10100;
  Array<float> read();

 public:
  IPC10100(char inBaseDID, unsigned long inPollingFrequency):
    Sensor(inBaseDID, inPollingFrequency) {};

  void begin();
};

#endif