#include "I2CTransceiver.hpp"

void I2CTransceiver::begin() {
  wire->begin();
}

bool I2CTransceiver::transmitFrame(byte txFrame[], size_t frameLength) {
  wire->beginTransmission(address);
  size_t numBytesTransmitted = wire->write(txFrame, frameLength);
  byte error = wire->endTransmission();

  if (numBytesTransmitted != frameLength || error != 0) {
    return false;
  }

  return true;
}

bool I2CTransceiver::receiveFrame(byte rxFrame[], size_t frameLength) {
  size_t bytesToRead = wire->requestFrom(address, frameLength);
  if (bytesToRead != frameLength) {
    return false;
  }

  int currentByte = -1;
  for(size_t i = 0; i < bytesToRead; i++){
    currentByte = wire->read();
    if (currentByte == -1) {
      return false;
    }

    rxFrame[i] = (byte) currentByte;
  }

  return true;
}