#include "Relay.hpp"


void Relay::begin() {
  pinMode(getPin(), OUTPUT);
  actuateState(getStates().read(0));
}

void Relay::actuateState(int desiredStateValue) {
  digitalWrite(getPin(), desiredStateValue);
}