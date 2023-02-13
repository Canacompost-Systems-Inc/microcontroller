#include "RotaryValve.hpp"

void RotaryValve::begin() {
  // Setup pins
  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(limitSwitchPin, INPUT);

  // move valve to start position
  Actuator::setState(startState);
}

void RotaryValve::actuateState(int desiredStateValue) {
  resetPosition();

  // Move motor number of steps to achieve the desired state (defined in Config.hpp)
  for (int i = 0; i < desiredStateValue; i++) {
    step();
  }
}

void RotaryValve::resetPosition() {
  // TODO: Error checking if limit switch is not hit
  digitalWrite(dirPin, COUNTER_CLOCKWISE);
  delay(PULSE_DELAY); // Ensure dir pin signal is fully propagated

  while (true) {
    if (digitalRead(limitSwitchPin) == LOW) {
      // Limit switch opened, start position reached
      break;
    }
    
    step();
  }

  // set dir to clockwise for actuateState to call
  digitalWrite(dirPin, CLOCKWISE);
  delay(PULSE_DELAY);
}

void RotaryValve::step() {
  // Does one motor step
  digitalWrite(pulPin, HIGH);
  delayMicroseconds(PULSE_DELAY);
  digitalWrite(pulPin, LOW);
  delayMicroseconds(PULSE_DELAY);
}