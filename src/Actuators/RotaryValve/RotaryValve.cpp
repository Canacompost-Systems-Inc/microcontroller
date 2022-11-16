#include "RotaryValve.hpp"


void RotaryValve::begin() {
  // Setup pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT);

  // Set the direction to clockwise
  digitalWrite(DIR_PIN, HIGH);

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
  // Moves valve back to starting postion
  // Does one full rotation, stops when limit switch is hit at position 1
  for (int i = 0; i < 6 * DELTA_STEPS; i++) {
    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      // Reached starting position
      break;
    }
    
    step();
  }

  // TODO: Error checking if limit switch is not hit
}

void RotaryValve::actuateState(int desiredStateValue) {
  int numStepsDistance = desiredStateValue - getCurrentStateValue();

  if (numStepsDistance < 0) {
    // Move to start position (ie: 1) then calculate number of moves to 
    // the desired position
    resetPosition();
    numStepsDistance = desiredStateValue;
  }

  // Spin the stepper motor by sending controlled pulse
  for (int i = 0; i < numStepsDistance * DELTA_STEPS; i++) {
    step();
  }
}