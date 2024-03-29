#ifndef FLAP_DIVERTER_VALVE_H
#define FLAP_DIVERTER_VALVE_H

#include "Actuator.hpp"
#include "Servo.h"

class FlapDiverterValve: public Actuator {
 public:
  FlapDiverterValve(char inDid, int inSignalPin, const Array<int> &inStates): 
    Actuator(inDid, inStates), signalPin(inSignalPin) {};
  void begin();
  void actuateState(int desiredStateValue);
  
 private:
  Servo servo;
  int signalPin;

};

#endif