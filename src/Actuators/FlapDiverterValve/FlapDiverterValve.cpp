#include "FlapDiverterValve.hpp"


void FlapDiverterValve::begin() {
  servo.attach(getPin());
  actuateState(getStates().read(0));
}

void FlapDiverterValve::actuateState(int desiredStateValue) {
  servo.write(desiredStateValue);
}