#include "SHT40I2CAdapter.hpp"

// declare consts here so it generates an address to reference 
const byte SHT40I2CAdapter::RESET_COMMAND;
const byte SHT40I2CAdapter::GET_ID_COMMAND;
const byte SHT40I2CAdapter::GET_DATA_COMMAND;

void SHT40I2CAdapter::begin() {
  i2cBus.begin();
  communicateWithI2CBus((byte *) &RESET_COMMAND, NULL, 0);

  // Delay extra time for startup
  delayMicroseconds(1000);
}

uint32_t SHT40I2CAdapter::getDeviceID() {
  uint32_t id = 0;
  size_t idArraySize = 6;
  byte idArray[6];

  communicateWithI2CBus((byte *) &GET_ID_COMMAND, idArray, idArraySize);

  bool crcIsValid = checkCrc(idArray[0], idArray[1], idArray[2]) && checkCrc(idArray[3], idArray[4], idArray[5]);
  if(crcIsValid) {
    id = ((uint32_t)idArray[0] << 24) | ((uint32_t)idArray[1] << 16) | ((uint32_t)idArray[3] << 8) | idArray[4];
  }
  
  return id;
}

bool SHT40I2CAdapter::getReading(float &temperature, float &humidity) {
  uint16_t rawTemperature;
  uint16_t rawHumidity;
  int errorCount = 0;

  while(!getRawData(rawTemperature, rawHumidity)) {
    if(errorCount > 10) {
      return false;
    }

    delay(1);
    errorCount++;
  }

  temperature = -45 + 175 * ((float)rawTemperature / 65536);
  humidity = -6 + 125 * ((float)rawHumidity / 65535);
  return true;
}

void SHT40I2CAdapter::runHeater(uint8_t powerMode) {
  communicateWithI2CBus((byte *) &powerMode, NULL, 0);
}

bool SHT40I2CAdapter::checkCrc(uint8_t data1, uint8_t data2, uint8_t crcValue) {
  uint8_t crc = 0xFF;
  uint8_t crcData[2];
  crcData[0] = data1;
  crcData[1] = data2;
  bool ret = true;

  for(int i = 0; i < 2; i++ ) {
    crc ^= crcData[i];
    for(uint8_t bit = 8; bit > 0; --bit) {
      if(crc & 0x80) {
        crc = ( crc << 1 ) ^ 0x31;
      } else {
        crc = ( crc << 1 );
      }
    }
  }

  if(crc != crcValue) {
    ret = false;
  }

  return ret;
}

bool SHT40I2CAdapter::getRawData(uint16_t &rawTemperature, uint16_t &rawHumidity) {
  size_t rawDataSize = 6;
  byte rawData[rawDataSize];

  communicateWithI2CBus((byte *) &GET_DATA_COMMAND, rawData, rawDataSize);

  bool crcIsValid = checkCrc(rawData[0], rawData[1], rawData[2]) && checkCrc(rawData[3], rawData[4], rawData[5]);
  if(!crcIsValid) {
    return false;
  }

  rawTemperature = (rawData[0] << 8) | rawData[1];
  rawHumidity = (rawData[3] << 8) | rawData[4];
  return true;
}

void SHT40I2CAdapter::communicateWithI2CBus(byte *command, byte *outputBuffer, size_t outputBufferLength) {
  i2cBus.transmitFrame(command, 1);
  delayBeforeReadingWire(*command);
  i2cBus.receiveFrame(outputBuffer, outputBufferLength);
}


void SHT40I2CAdapter::delayBeforeReadingWire(byte command) {
  unsigned long waitTimeMs;

  switch(command) {
    case SHT40Config::PRECISION_HIGH:
      waitTimeMs = 9;
      break;
    case SHT40Config::PRECISION_MID:
      waitTimeMs = 5;
      break;
    case SHT40Config::PRECISION_LOW:
      waitTimeMs = 2;
      break;
    case SHT40Config::POWER_CONSUMPTION_H_HEATER_1S:
      waitTimeMs = 1200;
      break;
    case SHT40Config::POWER_CONSUMPTION_H_HEATER_100MS:
      waitTimeMs = 110;
      break;
    case SHT40Config::POWER_CONSUMPTION_M_HEATER_1S:
      waitTimeMs = 1100;
      break;
    case SHT40Config::POWER_CONSUMPTION_M_HEATER_100MS:
      waitTimeMs = 110;
      break;
    case SHT40Config::POWER_CONSUMPTION_L_HEATER_1S:
      waitTimeMs = 1100;
      break;
    case SHT40Config::POWER_CONSUMPTION_L_HEATER_100MS:
      waitTimeMs = 110;
      break;
    default :
      waitTimeMs = 8;
      break;
  }

  delay(waitTimeMs);
}