#ifndef SHT40_I2C_ADAPTER_H
#define SHT40_I2C_ADAPTER_H

#include <Arduino.h>
#include "SHT40Config.hpp"
#include "I2CTransceiver.hpp"

class SHT40I2CAdapter {
 public:
  SHT40I2CAdapter(): i2cBus(I2C_BASE_ADDRESS) {};

  /**
   * Resets sensor
   */
  void begin();

  /**
   * Get sensor unique identifier 
   * @return Return identifier for success, 0 for failure 
   */
  uint32_t getDeviceID();

  /**
   * Gets temperature and humidity readings from sensor
   * @param temperature variable to write temperature to
   * @param humidity variable to write humidity to
   * @return true if reading values are valid, else false
   */
  bool getReading(float &temperature, float &humidity);

  /**
   * Enable heater 
   * @param  mode  Heating mode, see SHT40Config.hpp for mode options 
   */
  void runHeater(uint8_t powerMode);

 private:
  static const byte I2C_BASE_ADDRESS = 0x44;
  static const byte RESET_COMMAND = 0x94;
  static const byte GET_ID_COMMAND = 0x89;
  static const byte GET_DATA_COMMAND = SHT40Config::PRECISION_HIGH;

  /**
   *  Recheck the obtained data to determine if they are correct 
   * @param  data1  High 8 bits to check value
   * @param  data2  LOW 8 bits to check value
   * @param  crcValue  Check value returned by the sensor
   * @return Check success return true ;Check failed return false
   */
  bool checkCrc(uint8_t data1, uint8_t data2, uint8_t crcValue);

  /**
   * Obtain raw data from sensor
   * @param  temp Pointer to the address of the original value of the temperature
   * @param  hun   Pointer to the address of the original value of the humidity
   * @return Is the data obtained correct? return true  The data is correct ; return false  The data  is incorrect
   */
  bool getRawData(uint16_t &rawTemperature, uint16_t &rawHumidity);

  /**
   * Send and receive data with the I2C bus
   * @param command Bytes to transmit to sensor
   * @param outputBuffer Buffer to store received bytes from sensor
   * @param outputBufferLength length of outputBuffer
   */
  void communicateWithI2CBus(byte *command, byte *outputBuffer, size_t outputBufferLength);

  /**
   * Enact a delay corrsponding to the command sent to the sensor
   * @param  command  Command to be sent to the sensor which determines the delay length
   */
  void delayBeforeReadingWire(byte command);

  I2CTransceiver i2cBus;
};

#endif
