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

// SHT40 Bus. MUX 16 multiplexes the SDA line so that we can read from each SHT40 sensor individually. Needed
// since SHT40's all have the same I2C base address.
MUX16 sht40Mux(13, 2, 7, 6, 5, 4);
SHT40 c0(0xC0, config::DEFAULT_POLLING_INTERVAL, sht40Mux, 0); // Shared air
SHT40 cb(0xCB, config::DEFAULT_POLLING_INTERVAL, sht40Mux, 1);

// Remaining shared air sensors
// TODO: This was returning CRC error, need to test connection
// SCD41 c1(0xC1, config::DEFAULT_POLLING_INTERVAL);
IPC10100 c2(0xC2, config::DEFAULT_POLLING_INTERVAL);

// Ozone sensors
SEN0321 c9(0xC9, config::DEFAULT_POLLING_INTERVAL, OZONE_ADDRESS_3); // Front of line
SEN0321 ca(0xCA, config::DEFAULT_POLLING_INTERVAL, OZONE_ADDRESS_0); // End of line

// Flow rate
YFS201 c7(0xC7, config::FAST_POLLING_INTERVAL, 25);

/** ----- ACTUATOR OBJECTS -----
 * Declare actuator objects using the states as defined in config.h. All devices to be used in operation must 
 * be appended into the actuators array.
 */
Array<Actuator*> actuators;

// Two state flap diverters
FlapDiverterValve e7(0xE7, 35, config::FD_TWO_STATES_E7);
FlapDiverterValve e8(0xE8, 41, config::FD_TWO_STATES_E8);
// FlapDiverterValve ea(0xEA, 32, config::FD_TWO_STATES); // Broken valve may add back later

// Ten state flap diverters
FlapDiverterValve eb(0xEB, 33, config::FD_TWENTY_STATES_EB);
FlapDiverterValve ec(0xEC, 34, config::FD_TWENTY_STATES_EC);

// 6 state rotary valves
RotaryValve e0(0xE0, 10, 11, 24, config::ROTARY_STATES_E0, 4);
RotaryValve e1(0xE1, 8, 9, 22, config::ROTARY_STATES_E1, 3);
RotaryValve e2(0xE2, 12, 13, 23, config::ROTARY_STATES_E2, 1);

// 16 relay module, active low
Relay e3(0xE3, 3, config::RELAY_ACTIVE_LOW_STATES);
Relay e4(0xE4, 4, config::RELAY_ACTIVE_LOW_STATES);
Relay e5(0xE5, 6, config::RELAY_ACTIVE_LOW_STATES);
Relay e6(0xE6, 5, config::RELAY_ACTIVE_LOW_STATES);
Relay f0(0xF0, 7, config::RELAY_ACTIVE_LOW_STATES);

// Water pump relays
Relay e9(0xE9, 26, config::RELAY_ACTIVE_LOW_STATES);
Relay f6(0xF6, 27, config::RELAY_ACTIVE_LOW_STATES);
Relay f8(0xF8, 28, config::RELAY_ACTIVE_LOW_STATES);
Relay fa(0xFA, 29, config::RELAY_ACTIVE_LOW_STATES);

// Other Relays
Relay f1(0xF1, 2, config::RELAY_ACTIVE_LOW_STATES); // Blower
Relay f2(0xF2, 48, config::RELAY_ACTIVE_LOW_STATES); // BSF LEDs
Relay f3(0xF3, 49, config::RELAY_ACTIVE_LOW_STATES); // Ozone gen
Relay f4(0xF4, 47, config::RELAY_ACTIVE_LOW_STATES); // UVC Light

void YSF201InterruptHandler() {
	c7.pulse();
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
  actuators.insert(&eb);
  actuators.insert(&ec);
  actuators.insert(&f0);
  actuators.insert(&e9);
  actuators.insert(&f6);
  actuators.insert(&f8);
  actuators.insert(&fa);
  actuators.insert(&f1);
  actuators.insert(&f2);
  actuators.insert(&f3);
  actuators.insert(&f4);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

// Inserts desired operational devices into sensors array and calls the begin function for each
void setupSensors() {
  sensors.insert(&c0);
  sensors.insert(&cb);
  // sensors.insert(&c1);
  sensors.insert(&c2);
  sensors.insert(&c7);
  sensors.insert(&c9);
  sensors.insert(&ca);

	for (int i = 0; i < sensors.getSize(); i++) {
		sensors.read(i)->begin();
	}

	// Attach interrupts
	attachInterrupt(digitalPinToInterrupt(c7.getSignalPin()), YSF201InterruptHandler, RISING);

	// Wait to allow for sensors to setup, without this sensor returns uninitialized value since it has not
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