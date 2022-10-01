#include "Actuator.hpp"


Actuator::Actuator(char inDid, int inPin, const Array<int> &inStates) {
  did = inDid;
  pin = inPin;
  currentState = 0;
  states = inStates;
}

bool Actuator::setState(int newState) {
  bool newStateInRange = (newState >= 0 && newState < states.getSize());
  if (!newStateInRange) {
    return false;
  }

  actuateState(states.read(newState));
  currentState = newState;
  return true;
}

int Actuator::getPin() {
  return pin;
}

Array<int> Actuator::getStates() {
  return states;
}

void Actuator::report() {
  Serial.write(did);
  const char *bytesPtr = reinterpret_cast<const char*>(&currentState);
  
  // Write out transmission block in little-endian (reverse order of bytesPtr)
  for(size_t j = 0; j != sizeof(int32_t); j++) {
    Serial.write(bytesPtr[sizeof(int32_t) - 1 - j]); 
  }
}