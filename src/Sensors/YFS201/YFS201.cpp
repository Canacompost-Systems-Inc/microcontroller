#include "YFS201.hpp"


Array<float> YFS201::read() {
  Array<float> reading;
  // calculate flow rate in L/min:
  //  From the data sheet, pulse_freq = 7.5 flow, where the flow rate is in L/min
  //  So, flow = pulse_freq / 7.5
  //  This function is called according to the polling frequency (ms), so we need to
  //  divide flow by the polling frequency in seconds
  float flow = (pulseFrequency / 7.5) / (getPollingFrequency() / 1000);
  pulseFrequency = 0;
  reading.insert(flow);
  return reading;
}

void YFS201::begin() {
  int configuredPin = getPin();
  pinMode(configuredPin, INPUT);
}

void YFS201::pulse() {
  pulseFrequency++;
}