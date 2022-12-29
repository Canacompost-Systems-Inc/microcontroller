#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Array.hpp"


class Actuator {
 private:
  byte did; 
  int32_t currentState; // using int32 to ensure payload of 4 bytes (consistent with sensor class)
  const Array<int> *states;

 public:
  /**
   * @param inDid Device ID, used for identifying actuator
   * @param inStates all possible states for this actuator (element 0 = state 0 with a state value equal to the 
   * value at that element)
   */
  Actuator(byte inDid, const Array<int> &inStates);

  /**
   * Inheriting class can override the begin() virtual function and implement any setup logic needed 
   * for actuator. If no override is present this function will do nothing.
   */ 
  virtual void begin() {};
  
  /**
   * Inheriting class is expected to override the actuateState and implement logic to update the state
   * of actuator. If no override is present this function will do nothing.
   * 
   * @param desiredStateValue Int value that the device is expected to be actuated to
   */
  virtual void actuateState(int desiredStateValue) {};

  /**
   * @param newState state to set actuator to
   * @return true if state was set, false if error occurred
   */ 
  bool setState(int newState);

  /**
   * @return device id
   */
  byte getDid();
  
  /** 
   * Returns the array of all possible states
   */
  Array<int> getStates();

  /*
   * Returns the index of the current state (ex: returns 0 signifying that the current state is state 0)
   */
  int getCurrentState();

  /*
   * Returns the value of the current state (ex: returns 100 corrsponding to the value of state 0)
   */
  int getCurrentStateValue();

  /**
   * Transmits actuator state in a package format.
   */
  void report();
};

#endif