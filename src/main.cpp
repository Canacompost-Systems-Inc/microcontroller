#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>

#include "Config.hpp"
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

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;
const unsigned long FAST_POLLING_INTERVAL = 1000;

/* ----- ACTUATOR STATES -----
 * Each actuator is given one of these arrays. The array represents all the possible states with the index
 * being the state id (ie: index 0 = state 0), and the value being the desired state to actuate to (with each 
 * actuator having its own domain).
 */

// 0=OFF, 1=OFF
static const Array<int> RELAY_STATES({0, 1});

// Rotation in degrees of the flap arm, diverts between two output valves. Note that the total rotation angle 
// (180 degrees) is much larger than the flap can physically do. This is due to these valves having different 
// starting positions (0 degrees). By having a large window we ensure that the flap is all the way to one side
// for all valves. The flaps have a mechanical stop when closed to one size. It is assumed that the torque 
// applied is constant no matter how far past the mechanical stop we actuate too, therefore this large window
// will not negatively effect the device.
static const Array<int> FD_TWO_STATES({0, 180});

// Rotation in degrees of the flap arm, controls how much air passes through by diverting to an...
// TODO: configure these for each device
static const Array<int> FD_TEN_STATES_EB({0, 38, 45, 51, 59, 66, 73, 80, 94, 180});
static const Array<int> FD_TEN_STATES_EC({0, 68, 124, 180});
static const Array<int> FD_TEN_STATES_F4({0, 30, 38, 46, 54, 62, 70, 78, 86, 180});

// TODO: Rename and configure these for rotary valve
static const Array<int> VALVE1_STATES({0, 2650, 5950, 9250, 12600, 15925, 19275}); // values tuned to RED YELOW valve

/** ----- OBJECTS -----
 * 
 */
// Actuators
// Relay relay0(0xE0, 13, RELAY_STATES);
// Relay relay1(0xE1, 13, RELAY_STATES);
// Relay relay2(0xE2, 13, RELAY_STATES);
// Relay relay3(0xE3, 13, RELAY_STATES);
// Relay relay4(0xE4, 13, RELAY_STATES);
// Relay relay5(0xE5, 13, RELAY_STATES);
// Relay relay6(0xE6, 13, RELAY_STATES);

// RotaryValve e0(0xE0, 2, VALVE1_STATES);
// RotaryValve e1(0xE1, 2, VALVE1_STATES);
// RotaryValve e2(0xE2, 2, VALVE1_STATES);

// Two state flap diverters
FlapDiverterValve e7(0xE7, 35, FD_TWO_STATES);
FlapDiverterValve e8(0xE8, 41, FD_TWO_STATES);
FlapDiverterValve ea(0xEA, 32, FD_TWO_STATES);

// Ten state flap diverters
// FlapDiverterValve eb(0xEB, 33, FD_TEN_STATES_EB);
// FlapDiverterValve ec(0xEC, 34, FD_TEN_STATES);
// FlapDiverterValve f4(0xF4, 42, FD_TEN_STATES_F4);


// Sensors
SHT40 	    sht40(0xC0, DEFAULT_POLLING_INTERVAL, -1);
SCD41 	    scd41(0xC1, DEFAULT_POLLING_INTERVAL, -1);
IPC10100 ipc10100(0xC2, DEFAULT_POLLING_INTERVAL, -1);
DS18B20	  ds18b20(0xC3, DEFAULT_POLLING_INTERVAL, 2);
// DS18B20	  ds18b20(0xC4, DEFAULT_POLLING_INTERVAL, 2);
// DS18B20	  ds18b20(0xC5, DEFAULT_POLLING_INTERVAL, 2); // TODO: need to update pins and names here
// DS18B20	  ds18b20(0xC6, DEFAULT_POLLING_INTERVAL, 2);
YFS201	   yfs201(0xC7, FAST_POLLING_INTERVAL, 3);
SEN0441	  sen0441(0xC8, DEFAULT_POLLING_INTERVAL, 10);
SEN0321	  sen0321(0xC9, DEFAULT_POLLING_INTERVAL, -1);

Array<Sensor*> sensors;
Array<Actuator*> actuators;
ControlUnit controller;

void YSF201InterruptHandler() {
	yfs201.pulse();
}

void setupActuators() {
  actuators.insert(&e7);
  actuators.insert(&e8);
  actuators.insert(&ea);
  // actuators.insert(&eb);
  // actuators.insert(&ec);
  // actuators.insert(&f4);
  // actuators.insert(&valve1);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

void setupSensors() {
	// sensors.insert(&sht40);
	// sensors.insert(&scd41);
	// sensors.insert(&yfs201);
  // sensors.insert(&sen0441);

	for (int i = 0; i < sensors.getSize(); i++) {
		sensors.read(i)->begin();
	}

	// Attach interrupts
	attachInterrupt(digitalPinToInterrupt(yfs201.getPin()), YSF201InterruptHandler, RISING);

	// Wait to allow for sensors to setup
  // TODO: replace this with a better strategy that handles config times for each sensor
	delay(DEFAULT_POLLING_INTERVAL);
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