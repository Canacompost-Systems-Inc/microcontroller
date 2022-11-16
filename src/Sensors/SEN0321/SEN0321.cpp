#include "SEN0321.hpp"


Array<float> SEN0321::read() {
  Array<float> reading;

  // gets concentration in PPM, converts uint16 to float data
  float ozoneConcentration = sen0321.readOzoneData(COLLECT_NUMBER);
  reading.insert(ozoneConcentration);
  
  return reading;
}

void SEN0321::begin() {
  while(!sen0321.begin(IIC_ADDRESS)) {
    Serial.println("I2c device number error !");
    // TODO: Handle this error case
    delay(1000);
  }

  // Set iic mode, active mode or passive mode
  //    active = MEASURE_MODE_PASSIVE
  //    passive = passive mode
  sen0321.setModes(MEASURE_MODE_PASSIVE);
}