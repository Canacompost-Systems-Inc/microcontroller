#ifndef SHT40I2CADAPTER_H
#define SHT40I2CADAPTER_H

#include <Arduino.h>
#include "SHT40Config.hpp"
#include "I2CTransceiver.hpp"


class SHT40I2CAdapter {
 public:
  SHT40I2CAdapter(): i2cBus(I2C_BASE_ADDRESS) {};

  void begin();

  /**
   * Get sensor unique identifier 
   * @return Return identifier for success, 0 for failure 
   */
  uint32_t getDeviceID();

  bool getReading(float &temperature, float &humidity);

  /**
   * @brief  Enable heater 
   * @param  mode  Heating mode 
   * @n                    POWER_CONSUMPTION_H_HEATER_1S                                  activate highest heater power & high precis. meas. for 1s 
   * @n                    POWER_CONSUMPTION_H_HEATER_100MS                               activate highest heater power & high precis. meas. for 0.1s
   * @n                    POWER_CONSUMPTION_M_HEATER_1S                                   activate medium heater power  & high precis. meas. for 1s 
   * @n                    POWER_CONSUMPTION_M_HEATER_100MS                                activate medium heater power  & high precis. meas. for 0.1s 
   * @n                    POWER_CONSUMPTION_L_HEATER_1S                                   activate lowest heater power  & high precis. meas. for 1s 
   * @n                    POWER_CONSUMPTION_L_HEATER_100MS                                activate lowest heater power  & high precis. meas. for 0.1s 
   */
  void runHeater(uint8_t powerMode);

 private:
  /**
   * Obtain raw data from sensor
   * @param  temp Pointer to the address of the original value of the temperature
   * @param  hun   Pointer to the address of the original value of the humidity
   * @return Is the data obtained correct? return true  The data is correct ; return false  The data  is incorrect
   */
  bool getRawData(uint16_t &rawTemperature, uint16_t &rawHumidity);

  void delayBeforeReadingWire(byte command);

  /**
   * @brief  Recheck the obtained data to determine if they are correct 
   * @param  data1  High 8 bits to check value
   * @param  data2  LOW 8 bits to check value
   * @param  crcValue  Check value returned by the sensor
   * @return Check success return true ;Check failed return false
   */
  bool checkCrc(uint8_t data1, uint8_t data2, uint8_t crcValue);

  static const byte I2C_BASE_ADDRESS = 0x44;
  static const byte RESET_COMMAND = 0x94;
  static const byte GET_ID_COMMAND = 0x89;
  static const byte GET_DATA_COMMAND = SHT40Config::PRECISION_HIGH;

  I2CTransceiver i2cBus;
};

#endif
