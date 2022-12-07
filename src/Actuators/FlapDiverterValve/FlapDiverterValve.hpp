#ifndef FLAPDIVERTERVALVE_H
#define FLAPDIVERTERVALVE_H

#include "Actuator.hpp"
#include "Servo.h"

class FlapDiverterValve: public Actuator {
 private:
  Servo servo;
  int signalPin;

 public:
  FlapDiverterValve(char inDid, int inSignalPin, const Array<int> &inStates): 
    Actuator(inDid, inStates), signalPin(inSignalPin) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif