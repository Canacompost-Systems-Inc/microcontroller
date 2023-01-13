#include "SHT40.hpp"


Array<float> SHT40::read() {
  Array<float> reading;
  float temperature;
  float humidity;

  mux->select(muxChannel);

  bool readingIsValid = wire.getReading(temperature, humidity);
  if (!readingIsValid) {
    // TODO: handle error
    Serial.println("ERR:Checksum error in getReading!");
    return;
  }

  if (humidity > 80) {
    wire.runHeater(SHT40Config::POWER_CONSUMPTION_H_HEATER_1S);
  }

  reading.insert(temperature);
  reading.insert(humidity);
  return reading;
}

void SHT40::begin() {
  uint32_t id = 0;
  wire.begin();

  while((id = wire.getDeviceID()) == 0) {
    Serial.println("SHT40::begin() - Sensor failed to connect");
    delay(1000);
  }
}
