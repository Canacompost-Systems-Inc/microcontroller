#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>
#include <AccelStepper.h>
#include "Array.hpp"
#include "Sensors/MQx/MQx.hpp"
#include "Sensors/SHT40/SHT40.hpp"
#include "Sensors/SCD41/SCD41.hpp"
#include "Sensors/IPC10100/IPC10100.hpp"
#include "Sensors/DS18B20/DS18B20.hpp"
#include "Sensors/YFS201/YFS201.hpp"
#include "Sensors/SEN0441/SEN0441.hpp"
#include "Actuators/FlapDiverterValve/FlapDiverterValve.hpp"
#include "Actuators/Relay/Relay.hpp"
#include "ControlUnit/ControlUnit.hpp"

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;
const unsigned long FAST_POLLING_INTERVAL = 1000;
static const Array<int> RELAY_STATES({0, 1});
static const Array<int> VALVE0_STATES({35, 80, 130});

// ----- OBJECTS ----- //
// Actuators
Relay relay0(0xE0, 13, RELAY_STATES);
Relay relay1(0xE1, 13, RELAY_STATES);
Relay relay2(0xE2, 13, RELAY_STATES);
Relay relay3(0xE3, 13, RELAY_STATES);
Relay relay4(0xE4, 13, RELAY_STATES);
Relay relay5(0xE5, 13, RELAY_STATES);
Relay relay6(0xE6, 13, RELAY_STATES);
FlapDiverterValve valve0(0xE7, 2, VALVE0_STATES);

// Sensors
SHT40 	    sht40(0xC0, DEFAULT_POLLING_INTERVAL, -1);
SCD41 	    scd41(0xC1, DEFAULT_POLLING_INTERVAL, -1);
IPC10100 ipc10100(0xC2, DEFAULT_POLLING_INTERVAL, -1);
DS18B20	  ds18b20(0xC3, DEFAULT_POLLING_INTERVAL, 2);
YFS201	   yfs201(0xC4, FAST_POLLING_INTERVAL, 3);
SEN0441	  sen0441(0xC5, DEFAULT_POLLING_INTERVAL, 10);

Array<Sensor*> sensors;
Array<Actuator*> actuators;
ControlUnit controller;

AccelStepper step;

void YSF201InterruptHandler() {
	yfs201.pulse();
}

void setupActuators() {
  // actuators.insert(&relay0);
  // actuators.insert(&relay1);
  // actuators.insert(&relay2);
  // actuators.insert(&relay3);
  // actuators.insert(&relay4);
  // actuators.insert(&relay5);
  // actuators.insert(&relay6);
  // actuators.insert(&valve0);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

void setupSensors() {
	// sensors.insert(&sht40);
	// sensors.insert(&scd41);
	// sensors.insert(&yfs201);
  sensors.insert(&sen0441);

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
	// setupActuators();
	// setupSensors();
	// controller.begin(actuators, sensors);
  step.setMaxSpeed(1000000);
  // step.setSpeed(50000);
}

// Runs every clock cycle
void loop() {
	// controller.loop();
  step.moveTo(500000);
  step.setSpeed(50000);
  step.runSpeedToPosition();
}