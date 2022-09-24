#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Array.hpp"


class Actuator {
 private:
  static const byte B_HIGH = 0x11;
  static const byte B_LOW = 0x00;

  char did;
  int pin;
  byte state;

 protected:
  /**
   * @return pin value
   */
  int getPin();

 public:
  /**
   * @param inDid Device ID, used for identifying Actuator
   * @param inPin GPIO pin connected to the board 
   */
  Actuator(char inDid, int inPin);

  /**
   * Sets up actuator to closed state (LOW)
   */
  void begin();

  /**
   * Transmits actuator state in a package format.
   */
  void report();

  /**
   * @param newState state to set actuator to (HIGH or LOW)
   * @return true if state was set, false if error occurred
   */ 
  bool setState(byte newState);
};

#endif