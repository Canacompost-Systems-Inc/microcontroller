#include "MUX16.hpp"

const int MUX16::LUT[16][4] = {
  {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
  {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
  {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
  {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}
};

void MUX16::begin() {
  pinMode(enablePin, OUTPUT);

  for (int i=0; i<4; i++) {
    pinMode(selectorPin[i], OUTPUT);
  }

  enable();
}

void MUX16::select(int channel) {
  digitalWrite(selectorPin[0], LUT[channel][0]);
  digitalWrite(selectorPin[1], LUT[channel][1]);
  digitalWrite(selectorPin[2], LUT[channel][2]);
  digitalWrite(selectorPin[3], LUT[channel][3]);
}

void MUX16::enable() {
  digitalWrite(enablePin, LOW);
}

void MUX16::disable() {
  digitalWrite(enablePin, HIGH);
}