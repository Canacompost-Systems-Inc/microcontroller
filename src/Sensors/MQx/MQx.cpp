#include "MQx.hpp"


Array<float> MQx::read() {
  Array<float> reading;
  reading.insert(analogRead(getPin()));
  return reading;
}