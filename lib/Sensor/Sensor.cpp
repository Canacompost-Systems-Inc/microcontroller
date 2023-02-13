#include "Sensor.hpp"

Sensor::Sensor(byte inDid, unsigned long inPollingFrequency): 
  did(inDid), dataTimestamp(0), pollingFrequency(inPollingFrequency) {
  Array<float> emptyData;
  data = emptyData;
}

void Sensor::loop(unsigned long currentTimestamp) {
  if (errorCode == SensorErrors::SetupError) {
    // device was not able to setup properly, do not take readings
    return;
  }

  bool pollingIntervalElapsed = currentTimestamp - dataTimestamp >= pollingFrequency;
  if(pollingIntervalElapsed) {
    // reset error code to attempt to take a reading again
    errorCode = SensorErrors::NoError;

    Array<float> tempData = read();
    if(errorCode != SensorErrors::ReadError) {
      data = tempData;
      // Uncomment below to print current sensor data to serial monitor for debugging
      // debugReport();
    }

    dataTimestamp = currentTimestamp;
  }
}

void Sensor::report() {
  Serial.write(did);

  for(int i = 0; i < data.getSize(); i++) {
    float dataToWrite = data.read(i);
    const unsigned char *bytesPtr = reinterpret_cast<const unsigned char*>(&dataToWrite);

    // Write out transmission block in little-endian (reverse order of bytesPtr)
    for(size_t j = 0; j != sizeof(float); j++) {
      Serial.write(bytesPtr[sizeof(float) - 1 - j]); 
    }
  }
}

void Sensor::raiseError(SensorErrors newErrorCode) {
  errorCode = newErrorCode;
  printErrorMessage();
}

void Sensor::printErrorMessage() {
  Serial.print("\n");
  Serial.print("0x");
  Serial.print(did, HEX);
  Serial.print(": ");

  switch (errorCode) {
    case SensorErrors::SetupError:
      Serial.print("Setup Error");
      break;
    case SensorErrors::ReadError:
      Serial.print("Read Error");
      break;
    default:
      break;
  }
}

void Sensor::debugReport() {
  Serial.print("\n");
  Serial.print("0x");
  Serial.print(did, HEX);
  Serial.print(": ");

  for(int i = 0; i < data.getSize(); i++) {
    Serial.print(data.read(i));
    Serial.print(" ");
  }
}