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


/** ----- SENSOR OBJECTS -----
 * Declare sensor objects using the states as defined in config.h. All devices to be used in operation must 
 * be appended into the sensors array.
 */
Array<Sensor*> sensors;

SHT40 c0(0xC0, config::DEFAULT_POLLING_INTERVAL);
SCD41 c1(0xC1, config::DEFAULT_POLLING_INTERVAL);
IPC10100 c2(0xC2, config::DEFAULT_POLLING_INTERVAL);
YFS201 yfs201(0xC7, config::FAST_POLLING_INTERVAL, 3); // will need to update the pin

// BELOW SENSORS ARE NOT INTEGRATED YET
// DS18B20	  ds18b20(0xC3, config::DEFAULT_POLLING_INTERVAL, 2);
// DS18B20	  ds18b20(0xC4, config::DEFAULT_POLLING_INTERVAL, 2);
// DS18B20	  ds18b20(0xC5, config::DEFAULT_POLLING_INTERVAL, 2); // TODO: need to update pins and names here
// DS18B20	  ds18b20(0xC6, config::DEFAULT_POLLING_INTERVAL, 2);
// SEN0441	  sen0441(0xC8, config::DEFAULT_POLLING_INTERVAL, 10);
// SEN0321	  sen0321(0xC9, config::DEFAULT_POLLING_INTERVAL);

/** ----- ACTUATOR OBJECTS -----
 * Declare actuator objects using the states as defined in config.h. All devices to be used in operation must 
 * be appended into the actuators array.
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
RotaryValve e0(0xE0, 10, 11, 24, config::ROTARY_STATES_E0);
RotaryValve e1(0xE1, 8, 9, 22, config::ROTARY_STATES_E1);
RotaryValve e2(0xE2, 12, 13, 23, config::ROTARY_STATES_E2);

// 16 relay module, active low
Relay e3(0xE3, 3, config::RELAY_ACTIVE_LOW_STATES);
Relay e4(0xE4, 4, config::RELAY_ACTIVE_LOW_STATES);
Relay e5(0xE5, 6, config::RELAY_ACTIVE_LOW_STATES);
Relay e6(0xE6, 5, config::RELAY_ACTIVE_LOW_STATES);
Relay f0(0xF0, 7, config::RELAY_ACTIVE_LOW_STATES);

// Water pump relays
Relay e9(0xE9, 26, config::RELAY_ACTIVE_HIGH_STATES);
Relay f6(0xF6, 27, config::RELAY_ACTIVE_HIGH_STATES);
Relay f8(0xF8, 28, config::RELAY_ACTIVE_HIGH_STATES);
Relay fa(0xFA, 29, config::RELAY_ACTIVE_HIGH_STATES);

void YSF201InterruptHandler() {
	yfs201.pulse();
}

// Inserts desired operational devices into actuators array and calls the begin function for each
void setupActuators() {
  // Insert all operating actuators. Insert order has no effect.
  actuators.insert(&e0);
  actuators.insert(&e1);
  actuators.insert(&e2);
  actuators.insert(&e3);
  actuators.insert(&e4);
  actuators.insert(&e5);
  actuators.insert(&e6);
  actuators.insert(&e7); 
  actuators.insert(&e8);
  actuators.insert(&ea); 
  actuators.insert(&eb);
  actuators.insert(&ec);
  actuators.insert(&f0);
  actuators.insert(&f4);
  actuators.insert(&e9);
  actuators.insert(&f6);
  actuators.insert(&f8);
  actuators.insert(&fa);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

// Inserts desired operational devices into sensors array and calls the begin function for each
void setupSensors() {
  // sensors.insert(&c0);
  sensors.insert(&c1);
  sensors.insert(&c2);

	for (int i = 0; i < sensors.getSize(); i++) {
		sensors.read(i)->begin();
	}

	// Attach interrupts
	attachInterrupt(digitalPinToInterrupt(yfs201.getSignalPin()), YSF201InterruptHandler, RISING);

	// Wait to allow for sensors to setup, without this sensor returns uninitilized value since it has not
  // polled yet.
  // TODO: can we do without this wait? maybe take an initial reading in the setup
	delay(config::DEFAULT_POLLING_INTERVAL);
}

// Runs every time serial connection is established OR when arduino is powered on.
void setup() {
	Serial.begin(9600);

  // Build devices
	setupActuators();
	setupSensors();

  // Creates single instance for control unit with given actuators and sensors
	ControlUnit::begin(actuators, sensors);
}

// Runs every clock cycle
void loop() {
	ControlUnit::get()->loop();
}