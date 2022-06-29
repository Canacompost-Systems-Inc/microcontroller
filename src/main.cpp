#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>
#include <Wire.h>
#include "Sensor.hpp"
#include "Boards/MQX.hpp"
#include "Boards/SHT40.hpp"

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;

// ----- OBJECTS ----- //
MQX alcohol(0, DEFAULT_POLLING_INTERVAL);
MQX methane(1, DEFAULT_POLLING_INTERVAL);
MQX carbonMonoxide(2, DEFAULT_POLLING_INTERVAL);
MQX hydrogen(3, DEFAULT_POLLING_INTERVAL);
MQX gas(4, DEFAULT_POLLING_INTERVAL);
SHT40 temp(TEMP, DEFAULT_POLLING_INTERVAL);
SHT40 hum(HUM, DEFAULT_POLLING_INTERVAL);

void setup() 
{
	Serial.begin(9600);
	temp.begin();
	hum.begin();
}	

void loop() 
{
	unsigned long currentTimeMs = millis();

	alcohol.FSM(currentTimeMs);
	methane.FSM(currentTimeMs);
	carbonMonoxide.FSM(currentTimeMs);
	hydrogen.FSM(currentTimeMs);
	gas.FSM(currentTimeMs);

	temp.FSM(currentTimeMs);
	hum.FSM(currentTimeMs);
}

// TODO: integrate new code into existing code below

// #include <Wire.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>
// #include"DFRobot_SHT40.h"
// #include <icp101xx.h>


// // --------CONSTANTS ---------------
// // PINS: sensors
// // inlude here...
// const int ONE_WIRE_PIN = 16; // DS18B20 temp sensor pin
// const int CH4_SENSOR_PIN = A0;

// // PINS: actuators
// // inlude here...

// // -------- INITIALIZE SENSORS/ACTUATORS ---------------
// // Setup a oneWire instance to communicate with any OneWire device
// OneWire oneWire(ONE_WIRE_PIN);
// // Pass oneWire reference to DallasTemperature library
// DallasTemperature soilTempProbe( & oneWire);
// // Temperature and humidity breakout board(s): https://app.nuclino.com/Canacompost-Systems/Canacompost/IGNORE-Barometric-pressure-ICP-10100-a763c042-6a8d-4120-afab-ab3f2d3dcdbc
// DFRobot_SHT40 SHT40(SHT40_AD1B_IIC_ADDR); 
// // Barometric sensor Mikroe-3328: https://app.nuclino.com/Canacompost-Systems/Canacompost/IGNORE-Barometric-pressure-ICP-10100-a763c042-6a8d-4120-afab-ab3f2d3dcdbc
// ICP101xx mikroeBaroSensor;

// // Variables
// float soilTemp1 = 0;
// int methaneCH4 = 0;
// float temperature, humidity, airPressure;

// // Used to check if I2C devices are correctly connected
// uint32_t sht40_id = 0;

// void setup() {
//   // put your setup code here, to run once: 
//   Serial.begin(9600);

//   pinMode(LED_BUILTIN, OUTPUT);
//   soilTempProbe.begin();
//   SHT40.begin();
//   Wire.begin();

//   while((sht40_id = SHT40.getDeviceID()) == 0){
//     Serial.println("ID retrieval error, please check whether the device is connected correctly!!!");
//     delay(1000);
//   }

//   delay(1000);
//   Serial.print("sht40_id :0x. SHT40 sensor is connected"); Serial.println(sht40_id, HEX);

//   if (!mikroeBaroSensor.begin()) {
// 	  Serial.println("Mikroe-3328 baro sensor failed to connect");
//   }

//   if (mikroeBaroSensor.isConnected()) {
// 	  Serial.println("Mikroe-3328 baro sensor is connected");
//   } 
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(500);                       // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//   delay(500);                       // wait for a second

//   soilTempProbe.requestTemperatures();
//   soilTemp1 =  soilTempProbe.getTempCByIndex(0);
//   // Serial.print(F("Soil temp: ")); Serial.print(soilTemp1); Serial.println(" C");

//   methaneCH4 = analogRead(CH4_SENSOR_PIN);
//   // Serial.print(F(" methane: ")); Serial.print(methaneCH4); Serial.println("%");

//   temperature = SHT40.getTemperature(PRECISION_HIGH);
//   humidity = SHT40.getHumidity(PRECISION_HIGH);
//   if(temperature == MODE_ERR){
//     Serial.println("Incorrect mode configuration to get temperature");
//   } else{
//     Serial.print("Temperature :"); Serial.print(temperature); Serial.println(" C");
//   }
//   if(humidity == MODE_ERR){
//     Serial.println("The mode for getting humidity was misconfigured");
//   } else{
//     Serial.print("Humidity :"); Serial.print(humidity); Serial.println(" %RH");
//   }

//   if(humidity > 80){
//   /**
//    *    mode 
//    *                  POWER_CONSUMPTION_H_HEATER_1S                        activate highest heater power & high precis. meas. for 1s 
//    *                  POWER_CONSUMPTION_H_HEATER_100MS                     activate highest heater power & high precis. meas. for 0.1s
//    *                  POWER_CONSUMPTION_M_HEATER_1S                         activate medium heater power  & high precis. meas. for 1s 
//    *                  POWER_CONSUMPTION_M_HEATER_100MS                      activate medium heater power  & high precis. meas. for 0.1s 
//    *                  POWER_CONSUMPTION_L_HEATER_1S                         activate lowest heater power  & high precis. meas. for 1s 
//    *                  POWER_CONSUMPTION_L_HEATER_100MS                      activate lowest heater power  & high precis. meas. for 0.1s 
//    */
//     SHT40.enHeater(/*mode = */POWER_CONSUMPTION_H_HEATER_1S);
//   }

//   if (mikroeBaroSensor.dataReady()) {
//     // Read and output measured temperature in Fahrenheit and pressure in
// 	// Pascal.
//     Serial.print(mikroeBaroSensor.getTemperatureC());
//     Serial.print(" C, ");
//     Serial.print(mikroeBaroSensor.getPressurePa());
//     Serial.println(" P");

// 	// And start the next measurement cycle.
//     mikroeBaroSensor.measureStart(mikroeBaroSensor.VERY_ACCURATE);
//   }
//   Serial.println("--------------------------------------------------------------------");
// }