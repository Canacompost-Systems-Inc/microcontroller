#include "Sensor.hpp"


Sensor::Sensor(char inDid, unsigned long inPollingFrequency, int inPin) {
  dataTimestamp = 0;
  did = inDid;
  pollingFrequency = inPollingFrequency;
  pin = inPin;

  Array<float> emptyData;
  data = emptyData;
}

void Sensor::debugReport() {
  Serial.print("\n");
  Serial.print(" [");
  Serial.print(dataTimestamp);
  Serial.print("]: ");

  for(int i = 0; i < data.getSize(); i++) {
    Serial.print(data.read(i));
    Serial.print(' ');
  }
}

void Sensor::report() {
  Serial.write(did);

  // Send float value DATA_ARRAY_SIZE number of times
  for(int i = 0; i < data.getSize(); i++) {
    float dataToWrite = data.read(i);
    const unsigned char *bytesPtr = reinterpret_cast<const unsigned char*>(&dataToWrite);

    // Write out transmission block in little-endian (reverse order of bytesPtr)
    for(size_t j = 0; j != sizeof(float); j++) {
      Serial.write(bytesPtr[sizeof(float) - 1 - j]); 
    }
  }
}

void Sensor::loop(unsigned long currentTimestamp) {
  // Take reading once polling interval elapsed
  if(currentTimestamp - dataTimestamp >= pollingFrequency) {
    data = read();
    dataTimestamp = currentTimestamp;
  }
}

unsigned long Sensor::getPollingFrequency() {
  return pollingFrequency;
}

int Sensor::getPin() {
  return pin;
}

void Sensor::setPollingFrequency(unsigned long newPollingFrequency) {
  pollingFrequency = newPollingFrequency;
}