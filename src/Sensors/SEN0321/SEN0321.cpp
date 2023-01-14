#include "SEN0321.hpp"

void SEN0321::begin() {
  if (!sen0321.begin(baseAddress)) {
    raiseError(SensorErrors::SetupError);
  }
 
  // Set iic mode, active mode or passive mode
  //    active = MEASURE_MODE_PASSIVE
  //    passive = passive mode
  sen0321.setModes(MEASURE_MODE_PASSIVE);
}

Array<float> SEN0321::read() {
  Array<float> reading;

  // gets concentration in PPM, converts uint16 to float data
  float ozoneConcentration = sen0321.readOzoneData(COLLECT_NUMBER);
  if (ozoneConcentration == -1) {
    raiseError(SensorErrors::ReadError);
    return reading;
  }

  reading.insert(ozoneConcentration);

  return reading;
}