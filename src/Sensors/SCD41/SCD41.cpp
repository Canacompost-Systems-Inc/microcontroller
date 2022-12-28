#include "SCD41.hpp"


Array<float> SCD41::read() {
  Array<float> reading;
  uint16_t error;
  char errorMessage[256];
  uint16_t co2;
  float temperature;
  float humidity;

  error = scd41.readMeasurement(co2, temperature, humidity);
  if (error) {
    // TODO: handle error
    Serial.print("Error trying to execute readMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    return;
  }

  reading.insert(co2);
  reading.insert(temperature);
  reading.insert(humidity);
  return reading;
}

void SCD41::begin() {
  uint16_t error;
  char errorMessage[256];
  uint16_t serial0;
  uint16_t serial1;
  uint16_t serial2;

  Wire.begin();
  scd41.begin(Wire);

  // stop potentially previously started measurement
  error = scd41.stopPeriodicMeasurement();
  while (error) {
    Serial.print("SCD41::begin() - Error trying to execute stopPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    error = scd41.stopPeriodicMeasurement();
    delay(1000);
  }

  error = scd41.getSerialNumber(serial0, serial1, serial2);
  while (error) {
    Serial.print("SCD41::begin() - Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    error = scd41.getSerialNumber(serial0, serial1, serial2);
    delay(1000);
  }

  // Start Measurement proccess
  error = scd41.startPeriodicMeasurement();
  while (error) {
    Serial.print("SCD41::begin() - Error trying to execute startPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    error = scd41.startPeriodicMeasurement();
    delay(1000);
  }
}