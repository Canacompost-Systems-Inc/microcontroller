#include "Relay.hpp"

void Relay::begin() {
  pinMode(signalPin, OUTPUT);
  actuateState(getStates().read(0));
}

void Relay::actuateState(int desiredStateValue) {
  digitalWrite(signalPin, desiredStateValue);
}