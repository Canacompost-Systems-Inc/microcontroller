#include "RotaryValve.hpp"


void RotaryValve::begin() {
  // Setup pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT);

  // move output to start position
  resetPosition();
}

void RotaryValve::step() {
  // Does one motor step
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(PULSE_DELAY);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(PULSE_DELAY);
}

void RotaryValve::resetPosition() {
  // Moves valve back to starting postion where limit switch is open
  // TODO: Error checking if limit switch is not hit

  // Move cc back to start position
  digitalWrite(DIR_PIN, COUNTER_CLOCKWISE);

  while (true) {
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      break;
    }
    
    step();
  }

  // set dir to clockwise for actuateState to call
  digitalWrite(DIR_PIN, CLOCKWISE);
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