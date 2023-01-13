#ifndef SHT40CONFIG_H
#define SHT40CONFIG_H

#include <Arduino.h>


namespace SHT40Config {

// Precision modes for reading measurements
static const byte PRECISION_HIGH = 0xFD; // measure T & RH with high precision (high repeatability)
static const byte PRECISION_MID = 0xF6; // measure T & RH with medium precision (medium repeatability)
static const byte PRECISION_LOW = 0xE0; // measure T & RH with lowest precision (low repeatability)

// Power consumption modes for heater
static const byte POWER_CONSUMPTION_H_HEATER_1S = 0x39; // activate highest heater power & high precis. meas. for 1s
static const byte POWER_CONSUMPTION_H_HEATER_100MS = 0x32; // activate highest heater power & high precis. meas. for 0.1s
static const byte POWER_CONSUMPTION_M_HEATER_1S = 0x2F; // activate medium heater power  & high precis. meas. for 1s
static const byte POWER_CONSUMPTION_M_HEATER_100MS = 0x24; // activate medium heater power  & high precis. meas. for 0.1s
static const byte POWER_CONSUMPTION_L_HEATER_1S = 0x1E; // activate lowest heater power  & high precis. meas. for 1s
static const byte POWER_CONSUMPTION_L_HEATER_100MS = 0x15; // activate lowest heater power  & high precis. meas. for 0.1s

}

#endif