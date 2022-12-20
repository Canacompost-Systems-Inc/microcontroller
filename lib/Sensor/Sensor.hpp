#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Array.hpp"


class Sensor {
 private:
  static const int DATA_ARRAY_SIZE = 3;

  byte did;
  Array<float> data;
  unsigned long dataTimestamp;
  unsigned long pollingFrequency;

  /**
   * Used to print data to serial monitor when debugging.
   */
  void debugReport();

 protected:
  /**
   * Inheriting class should override the read() virtual function and implement the logic for reading 
   * from sensor. If no override is present will return current value of data. 
   */
  virtual Array<float> read() { return data; };

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
  byte getDid();

  /**
   * @return current value for pollingFrequency
   */
  unsigned long getPollingFrequency();

  /**
   * @param newPollingFrequency milliseconds of new desired frequency
   */
  void setPollingFrequency(unsigned long newPollingFrequency);
};

#endif