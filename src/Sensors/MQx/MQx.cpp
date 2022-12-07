#include "MQx.hpp"


Array<float> MQx::read() {
  Array<float> reading;
  reading.insert(analogRead(analogSignalPin));
  return reading;
}