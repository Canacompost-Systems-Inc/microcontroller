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
  static const int LIMIT_SWITCH_PIN = 7;

  int startOffset;

  void step();
  void resetPosition();

 public:
  RotaryValve(char inDid, int inPin, const Array<int> &inStates, int inStartOffset): 
    Actuator(inDid, inPin, inStates), startOffset(inStartOffset) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif