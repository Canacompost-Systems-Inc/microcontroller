#ifndef SHT40_H
#define SHT40_H

#include "Sensor.hpp"
#include "DFRobot_SHT40.h"
#include "MUX16.hpp"


class SHT40: public Sensor {
 private:
  DFRobot_SHT40 sht40;
  MUX16 *mux;
  int muxChannel;
  Array<float> read();

 public:
  SHT40(char inBaseDID, unsigned long inPollingFrequency, MUX16 &inMux, int inMuxChannel):
    Sensor(inBaseDID, inPollingFrequency), sht40(SHT40_AD1B_IIC_ADDR), 
    mux(&inMux), muxChannel(inMuxChannel) {};

  void begin();
};

#endif