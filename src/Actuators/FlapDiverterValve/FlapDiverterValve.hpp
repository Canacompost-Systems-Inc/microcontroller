#ifndef FLAPDIVERTERVALVE_H
#define FLAPDIVERTERVALVE_H

#include "Actuator.hpp"
#include "Servo.h"

class FlapDiverterValve: public Actuator {
 private:
  Servo servo;

 public:
  FlapDiverterValve(char inDid, int inPin, const Array<int> &inStates): 
    Actuator(inDid, inPin, inStates) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif