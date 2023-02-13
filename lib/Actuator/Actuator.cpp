#include "Actuator.hpp"

Actuator::Actuator(byte inDid, const Array<int> &inStates) {
  did = inDid;
  currentState = 0;
  states = &inStates;
}

bool Actuator::setState(int newState) {
  bool newStateIsInRange = (newState >= 0 && newState < states->getSize());
  if (!newStateIsInRange) {
    return false;
  }

  int newStateValue = states->read(newState);
  actuateState(newStateValue);
  currentState = newState;
  
  return true;
}

byte Actuator::getDid() {
  return did;
}

Array<int> Actuator::getStates() {
  return *states;
}

int Actuator::getCurrentState() {
  return currentState;
}

int Actuator::getCurrentStateValue() {
  return states->read(currentState);
}

void Actuator::report() {
  Serial.write(did);
  const char *bytesPtr = reinterpret_cast<const char*>(&currentState);
  
  // Write out transmission block in little-endian (reverse order of bytesPtr)
  for(size_t j = 0; j != sizeof(int32_t); j++) {
    Serial.write(bytesPtr[sizeof(int32_t) - 1 - j]); 
  }
}