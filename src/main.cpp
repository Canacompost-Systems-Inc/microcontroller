#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>

#include "config.hpp"
#include "Array.hpp"
#include "Sensors/MQx/MQx.hpp"
#include "Sensors/SHT40/SHT40.hpp"
#include "Sensors/SCD41/SCD41.hpp"
#include "Sensors/IPC10100/IPC10100.hpp"
#include "Sensors/DS18B20/DS18B20.hpp"
#include "Sensors/YFS201/YFS201.hpp"
#include "Sensors/SEN0441/SEN0441.hpp"
#include "Sensors/SEN0321/SEN0321.hpp"
#include "Actuators/FlapDiverterValve/FlapDiverterValve.hpp"
#include "Actuators/Relay/Relay.hpp"
#include "Actuators/RotaryValve/RotaryValve.hpp"
#include "ControlUnit/ControlUnit.hpp"

// Main instance for control unit (should only be 1)
ControlUnit controller;

/** ----- SENSOR OBJECTS -----
 * Declare sensor objects using the states as defined in config.h. All devices to be used in operation must 
 * be appended into the actuators array in the order of their desired device ids (element 0 = DID 0xC0 
 * and element 32 = DID 0xDF)
 */

Array<Sensor*> sensors;

SHT40 	    sht40(0xC0, config::DEFAULT_POLLING_INTERVAL, -1);
SCD41 	    scd41(0xC1, config::DEFAULT_POLLING_INTERVAL, -1);
IPC10100 ipc10100(0xC2, config::DEFAULT_POLLING_INTERVAL, -1);
DS18B20	  ds18b20(0xC3, config::DEFAULT_POLLING_INTERVAL, 2);
// DS18B20	  ds18b20(0xC4, config::DEFAULT_POLLING_INTERVAL, 2);
// DS18B20	  ds18b20(0xC5, config::DEFAULT_POLLING_INTERVAL, 2); // TODO: need to update pins and names here
// DS18B20	  ds18b20(0xC6, config::DEFAULT_POLLING_INTERVAL, 2);
YFS201	   yfs201(0xC7, config::FAST_POLLING_INTERVAL, 3);
SEN0441	  sen0441(0xC8, config::DEFAULT_POLLING_INTERVAL, 10);
SEN0321	  sen0321(0xC9, config::DEFAULT_POLLING_INTERVAL, -1);

/** ----- ACTUATOR OBJECTS -----
 * Declare actuator objects using the states as defined in config.h. All devices to be used in operation must 
 * be appended into the actuators array in the order of their desired device ids (element 0 = DID 0xE0 
 * and element 32 = DID 0xFF)
 */

Array<Actuator*> actuators;

// Two state flap diverters
FlapDiverterValve e7(0xE7, 35, config::FD_TWO_STATES);
FlapDiverterValve e8(0xE8, 41, config::FD_TWO_STATES);
FlapDiverterValve ea(0xEA, 32, config::FD_TWO_STATES);

// Ten state flap diverters
FlapDiverterValve eb(0xEB, 33, config::FD_TWENTY_STATES_EB);
FlapDiverterValve ec(0xEC, 34, config::FD_TWENTY_STATES_EC);
FlapDiverterValve f4(0xF4, 42, config::FD_TWENTY_STATES_F4);

// 6 state rotary valves
RotaryValve e0(0xE0, 2, 1, config::ROTARY_STATES_E1);
// RotaryValve e1(0xE1, 2, 1, config::ROTARY_STATES_E1);
// RotaryValve e2(0xE2, 2, 1, config::ROTARY_STATES_E1);

void YSF201InterruptHandler() {
	yfs201.pulse();
}

// Inserts desired operational devices into actuators array and calls the begin function for each
void setupActuators() {
  actuators.insert(&e7);
  actuators.insert(&e8);
  actuators.insert(&ea);
  actuators.insert(&eb);
  actuators.insert(&ec);
  actuators.insert(&f4);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

// Inserts desired operational devices into sensors array and calls the begin function for each
void setupSensors() {
	for (int i = 0; i < sensors.getSize(); i++) {
		sensors.read(i)->begin();
	}

	// Attach interrupts
	attachInterrupt(digitalPinToInterrupt(yfs201.getPin()), YSF201InterruptHandler, RISING);

	// Wait to allow for sensors to setup
  // TODO: replace this with a better strategy that handles config times for each sensor
	delay(config::DEFAULT_POLLING_INTERVAL);
}

// Runs every time serial connection is established OR when arduino is powered on.
void setup() {
	Serial.begin(9600);
	setupActuators();
	setupSensors();
	controller.begin(actuators, sensors);
}

// Runs every clock cycle
void loop() {
	controller.loop();
}