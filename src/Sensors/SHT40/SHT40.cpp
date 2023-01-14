#include "SHT40.hpp"

void SHT40::begin() {
  wire.begin();

  uint32_t id = wire.getDeviceID();
  bool idIsInvalid = (id == 0);
  if(idIsInvalid) {
    raiseError(SensorErrors::SetupError);
  }
}

Array<float> SHT40::read() {
  Array<float> reading;
  float temperature;
  float humidity;

  mux->select(muxChannel);

  bool readingIsValid = wire.getReading(temperature, humidity);
  if (!readingIsValid) {
    raiseError(SensorErrors::ReadError);
    return reading;
  }

  if (humidity > 80) {
    wire.runHeater(SHT40Config::POWER_CONSUMPTION_H_HEATER_1S);
  }

  reading.insert(temperature);
  reading.insert(humidity);

  return reading;
}