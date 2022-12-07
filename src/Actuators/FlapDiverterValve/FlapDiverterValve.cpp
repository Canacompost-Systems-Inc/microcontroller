#include "FlapDiverterValve.hpp"


void FlapDiverterValve::begin() {
  servo.attach(signalPin);
  actuateState(getStates().read(0));
}

void FlapDiverterValve::actuateState(int desiredStateValue) {
  servo.write(desiredStateValue);
}