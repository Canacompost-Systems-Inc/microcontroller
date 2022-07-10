#include "SCD41.hpp"


void SCD41::read()
{
    uint16_t error;
    char errorMessage[256];
    uint16_t co2;
    float temperature;
    float humidity;

    error = scd41.readMeasurement(co2, temperature, humidity);
    if (error) 
    {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }

    clearData();
    data[0] = co2;
    data[1] = temperature;
    data[2] = humidity;
    valid[0] = true;
    valid[1] = true;
    valid[2] = true;
}

void SCD41::begin()
{
    uint16_t error;
    char errorMessage[256];
    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;

    Wire.begin();
    scd41.begin(Wire);

    // stop potentially previously started measurement
    error = scd41.stopPeriodicMeasurement();
    if (error) 
    {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }

    error = scd41.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }

    // Start Measurement proccess
    error = scd41.startPeriodicMeasurement();
    if (error) 
    {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        return;
    }
}