#ifndef SHT40_H
#define SHT40_H

#include "Sensor.hpp"
#include "SHT40Config.hpp"
#include "SHT40I2CAdapter.hpp"
#include "MUX16.hpp"


class SHT40: public Sensor {
 private:
  SHT40I2CAdapter wire;
  MUX16 *mux;
  int muxChannel;
  Array<float> read();

 public:
  SHT40(char inBaseDID, unsigned long inPollingFrequency, MUX16 &inMux, int inMuxChannel):
    Sensor(inBaseDID, inPollingFrequency), wire(), 
    mux(&inMux), muxChannel(inMuxChannel) {};

  void begin();
};

#endif