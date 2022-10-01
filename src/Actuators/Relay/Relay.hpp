#ifndef RELAY_H
#define RELAY_H

#include "Actuator.hpp"
#include "Array.hpp"

class Relay: public Actuator {
 public:
  Relay(char inDid, int inPin, const Array<int> &inStates): 
    Actuator(inDid, inPin, inStates) {};
  void begin();
  void actuateState(int desiredStateValue);
};

#endif