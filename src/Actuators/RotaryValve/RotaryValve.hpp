#ifndef ROTARYVALVE_H
#define ROTARYVALVE_H

#include "Actuator.hpp"


class RotaryValve: public Actuator {
 private:
  static const int PULSE_DELAY = 500;
  static const int DELTA_STEPS = 3333;
  static const int DIR_PIN = 2;
  static const int STEP_PIN = 3;
  static const int LIMIT_SWITCH_PIN = 7;

  void step();
  void resetPosition();

 public:
  RotaryValve(char inDid, int inPin, const Array<int> &inStates): 
    Actuator(inDid, inPin, inStates) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif