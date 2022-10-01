#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Array.hpp"


class Actuator {
 private:
  char did;
  int pin;
  int32_t currentState; // using int32 to ensure payload of 4 bytes (consistent with sensor class)
  Array<int> states;

 public:
  /**
   * @param inDid Device ID, used for identifying Actuator
   * @param inPin GPIO pin connected to the board 
   */
  Actuator(char inDid, int inPin, const Array<int> &inStates);

  /**
   * Inheriting class can override the begin() virtual function and implement any setup logic needed 
   * for actuator. If no override is present this function will do nothing.
   */ 
  virtual void begin() {};
  
  /**
   * Inheriting class is expected to override the actuateState and implement logic to update the state
   * of actuator. If no override is present this function will do nothing.
   */
  virtual void actuateState(int desiredStateValue) {};

  /**
   * @param newState state to set actuator to
   * @return true if state was set, false if error occurred
   */ 
  bool setState(int newState);

  /**
   * @return pin value
   */
  int getPin();

  /** 
   * @return states
   */
  Array<int> getStates();

  /**
   * Transmits actuator state in a package format.
   */
  void report();
};

#endif