#include "RotaryValve.hpp"


void RotaryValve::begin() {
  // Setup pins
  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(limitSwitchPin, INPUT);

  // move output to start position
  resetPosition();
}

void RotaryValve::step() {
  // Does one motor step
  digitalWrite(pulPin, HIGH);
  delayMicroseconds(PULSE_DELAY);
  digitalWrite(pulPin, LOW);
  delayMicroseconds(PULSE_DELAY);
}

void RotaryValve::resetPosition() {
  // TODO: Error checking if limit switch is not hit
  digitalWrite(dirPin, COUNTER_CLOCKWISE);

  while (true) {
    if (digitalRead(limitSwitchPin) == LOW) {
      // Limit switch opened, start position reached
      break;
    }
    
    step();
  }

  // set dir to clockwise for actuateState to call
  digitalWrite(dirPin, CLOCKWISE);
}

void RotaryValve::actuateState(int desiredStateValue) {
  resetPosition();

  // Need time to stop and change direction after reset
  delay(100);

  // Spin the stepper motor by sending controlled pulse
  for (int i = 0; i < desiredStateValue; i++) {
    step();
  }
}