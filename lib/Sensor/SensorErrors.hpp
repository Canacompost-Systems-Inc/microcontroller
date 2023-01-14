#ifndef SENSOR_ERRORS_HPP
#define SENSOR_ERRORS_HPP

#include <stdint.h>

enum class SensorErrors: uint16_t {
  NoError = 0,
  SetupError = 0x0911,
  ReadError = 0x0999,
};

#endif