#include "Sensor.hpp"


Sensor::Sensor(byte inDid, unsigned long inPollingFrequency) {
  dataTimestamp = 0;
  did = inDid;
  pollingFrequency = inPollingFrequency;

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

byte Sensor::getDid() {
  return did;
}

unsigned long Sensor::getPollingFrequency() {
  return pollingFrequency;
}

void Sensor::setPollingFrequency(unsigned long newPollingFrequency) {
  pollingFrequency = newPollingFrequency;
}