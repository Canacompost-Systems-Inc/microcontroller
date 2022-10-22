#include "SEN0441.hpp"


Array<float> SEN0441::read() {
  Array<float> reading;
  /**
    Gas type:
    MICS-4514 You can get all gas concentration
    MICS-5524 You can get the concentration of CH4, C2H5OH, H2, NH3, CO
    MICS-2714 You can get the concentration of NO2
      Methane          (CH4)    (1000 - 25000)PPM
      Ethanol          (C2H5OH) (10   - 500)PPM
      Hydrogen         (H2)     (1    - 1000)PPM
      Ammonia          (NH3)    (1    - 500)PPM
      Carbon Monoxide  (CO)     (1    - 1000)PPM
      Nitrogen Dioxide (NO2)    (0.1  - 10)PPM
  */
  float h2 = sen0441.getGasData(H2);
  reading.insert(h2);
  return reading;
}

void SEN0441::begin() {
  while(!sen0441.begin()) {
    Serial.println("NO Devices !");
    delay(1000);
  } Serial.println("Device connected successfully !");

  /**
    Gets the power mode of the sensor
    The sensor is in sleep mode when power is on,so it needs to wake up the sensor. 
    The data obtained in sleep mode is wrong
   */
  uint8_t mode = sen0441.getPowerState();
  if(mode == SLEEP_MODE) {
    sen0441.wakeUpMode();
    Serial.println("wake up sensor success!");
  }else{
    Serial.println("The sensor is wake up mode");
  }

  /**! UNCOMMENT TO CALIBRATE SENSOR, must do it in clean air (different environment than it reads from)
    Do not touch the sensor probe when preheating the sensor.
    Place the sensor in clean air.
    The default calibration time is 3 minutes.
  */
  // while(!sen0441.warmUpTime(CALIBRATION_TIME)) {
  //   Serial.println("Please wait until the warm-up time is over!");
  //   delay(1000);
  // }
}