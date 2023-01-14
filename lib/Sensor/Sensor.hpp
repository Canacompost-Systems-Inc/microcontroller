#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Array.hpp"
#include "SensorErrors.hpp"

class Sensor {
 public:
  /**
   * @param inDid Device ID, used for identifying sensor
   * @param inPollingFrequency number of milliseconds between data samples
   */
  Sensor(byte inDid, unsigned long inPollingFrequency);

  /**
   * Inheriting class can override the begin() virtual function and implement any setup logic needed 
   * for sensor. If no override is present this function will do nothing.
   */ 
  virtual void begin() {};

  /**
   * Sensor main loop, controls when to take readings from sensor based on the
   * desired pollingFrequency.
   * 
   * @param currentTimestamp arduino timestamp returned from the function millis()
   */ 
  void loop(unsigned long currentTimestamp);

  /**
   * Transmits sensor data in a package format.
   */
  void report();

  /**
   * @return device id
   */
  inline byte getDid() { return did; };

  /**
   * @return current value for pollingFrequency
   */
  inline unsigned long getPollingFrequency() {return pollingFrequency; };

 protected:
  /**
   * Inheriting class should override the read() virtual function and implement the logic for reading 
   * from sensor. If no override is present will return current value of data. 
   */
  virtual Array<float> read() { return data; };

  /**
   * Sets sensor errorCode to given newErrorCode.
   * 
   * @param newErrorCode error code to set, see SensorErrors.hpp for possible values
   */
  void raiseError(SensorErrors newErrorCode);

 private:
  /**
   * Prints the current error message to serial monitor.
   */
  void printErrorMessage();

  /**
   * Used to print data to serial monitor when debugging.
   */
  void debugReport();

  byte did;
  SensorErrors errorCode;
  Array<float> data;
  unsigned long dataTimestamp;
  unsigned long pollingFrequency;
};

#endif