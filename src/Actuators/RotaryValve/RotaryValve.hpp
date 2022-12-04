#ifndef ROTARYVALVE_H
#define ROTARYVALVE_H

#include "Actuator.hpp"


class RotaryValve: public Actuator {
 private:
  static const int CLOCKWISE = HIGH;
  static const int COUNTER_CLOCKWISE = LOW;
  static const int PULSE_DELAY = 300; // delay between pulses sent to stepper
  static const int DELTA_STEPS = 3298; // MAX step size == 19788
  static const int DIR_PIN = 2;
  static const int STEP_PIN = 3;

  int limitSwitchPin;

  void step();
  void resetPosition();

 public:
  RotaryValve(char inDid, int inPin, int inLimitSwitchPin, const Array<int> &inStates): 
    Actuator(inDid, inPin, inStates), limitSwitchPin(inLimitSwitchPin) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif