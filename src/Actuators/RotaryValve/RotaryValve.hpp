#ifndef ROTARY_VALVE_H
#define ROTARY_VALVE_H

#include "Actuator.hpp"

class RotaryValve: public Actuator {
 public:
  RotaryValve(char inDid, int inPulPin, int inDirPin, int inLimitSwitchPin, const Array<int> &inStates, int inStartState): 
    Actuator(inDid, inStates), pulPin(inPulPin), dirPin(inDirPin), limitSwitchPin(inLimitSwitchPin),
    startState(inStartState) {};
  void begin();
  void actuateState(int desiredStateValue);

 private:
  // Used for setting directions of spin
  static const int COUNTER_CLOCKWISE = LOW;
  static const int CLOCKWISE = HIGH;
  
  // delay between pulses sent to stepper in microsecond, with specified driver settings (TB6600 stepper motor driver with 
  // micro-steps = 1 and current = 1.0.) this is the shortest that was possible
  static const int PULSE_DELAY = 400;

  /**
   * Moves valve COUNTER_CLOCKWISE back to starting postion where limit switch is open (LOW). 
   */
  void resetPosition();

  /**
   * Sends one pulse to pulPin with a period of 2*PULSE_DELAY 
   */
  void step();

  int pulPin; // Pin to send pulses to
  int dirPin; // Pin to set spin direction
  int limitSwitchPin; // When this pin is LOW we know that the rotary valve is in position 0
  int startState; // State to actuate in begin()
};

#endif