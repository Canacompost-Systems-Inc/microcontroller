#include "DS18B20.hpp"

void DS18B20::begin() {
  ds18b20.begin();
}

Array<float> DS18B20::read() {
  Array<float> reading;
  ds18b20.requestTemperatures(); 
  reading.insert(ds18b20.getTempCByIndex(0));
  return reading;
}