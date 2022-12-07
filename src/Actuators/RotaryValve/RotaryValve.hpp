#ifndef ROTARYVALVE_H
#define ROTARYVALVE_H

#include "Actuator.hpp"


class RotaryValve: public Actuator {
 private:
  static const int COUNTER_CLOCKWISE = LOW;
  static const int CLOCKWISE = HIGH;

  // TODO: add settings used for stepper controller
  // MAX step size == 19788
  static const int PULSE_DELAY = 400; // delay between pulses sent to stepper

  int pulPin;
  int dirPin;
  int limitSwitchPin;

  void step();
  void resetPosition();

 public:
  RotaryValve(char inDid, int inPulPin, int inDirPin, int inLimitSwitchPin, const Array<int> &inStates): 
    Actuator(inDid, -1, inStates), pulPin(inPulPin), dirPin(inDirPin), limitSwitchPin(inLimitSwitchPin) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif