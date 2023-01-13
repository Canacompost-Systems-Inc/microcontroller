#ifndef I2TRANSCEIVER_H
#define I2TRANSCEIVER_H

#include <Arduino.h>
#include <Wire.h>

class I2CTransceiver {
 public:
  I2CTransceiver(byte address): wire(&Wire), address(address) {};
  void begin();

  /**
   * Writes frame bytes to sensor 
   * @param  txFrame bytes written to sensor
   * @param  frameLength number of bytes to write
   * @return true if transmission was successful
   */
  bool transmitFrame(byte txFrame[], size_t frameLength);

  /**
   * Reads frame from sensor into rxFrame
   * @param rxFrame Buffer to store read data
   * @param frameLength number of bytes to read
   * @return true if rxFrame contains valid data
   */
  bool receiveFrame(byte rxFrame[], size_t frameLength);

 private:
  TwoWire *wire;
  byte address; // I2C address of device
};

#endif
