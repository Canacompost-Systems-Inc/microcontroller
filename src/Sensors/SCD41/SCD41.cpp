#include "SCD41.hpp"

void SCD41::begin() {
  Wire.begin();
  scd41.begin(Wire);

  // stop potentially previously measurement proccess 
  uint16_t startPeriodicMeasurementError = scd41.stopPeriodicMeasurement();

  uint16_t serial0;
  uint16_t serial1;
  uint16_t serial2;
  uint16_t serialNumberError = scd41.getSerialNumber(serial0, serial1, serial2);

  // restart the measurement proccess
  uint16_t stopPeriodicMeasurementError = scd41.startPeriodicMeasurement();

  if (startPeriodicMeasurementError || serialNumberError || stopPeriodicMeasurementError) {
    raiseError(SensorErrors::SetupError);
  }
}

Array<float> SCD41::read() {
  Array<float> reading;
  uint16_t co2;
  float temperature;
  float humidity;

  uint16_t readError = scd41.readMeasurement(co2, temperature, humidity);
  if (readError) {
    raiseError(SensorErrors::ReadError);
    return reading;
  }

  reading.insert(co2);
  reading.insert(temperature);
  reading.insert(humidity);

  return reading;
}