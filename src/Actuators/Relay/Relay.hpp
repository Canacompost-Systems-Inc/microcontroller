#ifndef RELAY_H
#define RELAY_H

#include "Actuator.hpp"
#include "Array.hpp"

class Relay: public Actuator {
 private:
  int signalPin;

 public:
  Relay(char inDid, int inSignalPin, const Array<int> &inStates): 
    Actuator(inDid, inStates), signalPin(inSignalPin) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif