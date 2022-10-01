#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>
#include "Array.hpp"
#include "Sensors/MQx/MQx.hpp"
#include "Sensors/SHT40/SHT40.hpp"
#include "Sensors/SCD41/SCD41.hpp"
#include "Sensors/IPC10100/IPC10100.hpp"
#include "Sensors/DS18B20/DS18B20.hpp"
#include "Actuators/FlapDiverterValve/FlapDiverterValve.hpp"
#include "Actuators/Relay/Relay.hpp"
#include "ControlUnit/ControlUnit.hpp"

// ----- CONSTANTS ----- //
static const unsigned long DEFAULT_POLLING_INTERVAL = 5000;
static const Array<int> RELAY_STATES({0, 1});
static const Array<int> VALVE0_STATES({35, 80, 130});

// ----- OBJECTS ----- //
// Actuators
Relay relay0(0xE0, 13, RELAY_STATES);
FlapDiverterValve valve0(0xE1, 12, VALVE0_STATES);

// Sensors
SHT40 	    sht40(0xC0, DEFAULT_POLLING_INTERVAL, -1);
SCD41 	    scd41(0xC1, DEFAULT_POLLING_INTERVAL, -1);
IPC10100 ipc10100(0xC2, DEFAULT_POLLING_INTERVAL, -1);
DS18B20	  ds18b20(0xC3, DEFAULT_POLLING_INTERVAL, 2);

Array<Sensor*> sensors;
Array<Actuator*> actuators;
ControlUnit controller;

void setupActuators() {
  actuators.insert(&relay0);
  actuators.insert(&valve0);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

void setupSensors() {
	sensors.insert(&sht40);
	sensors.insert(&scd41);

	for (int i = 0; i < sensors.getSize(); i++) {
		sensors.read(i)->begin();
	}

	// Wait to allow for sensors to setup
	delay(DEFAULT_POLLING_INTERVAL);
}

//  Runs every time serial connection is established OR when arduino is powered on.
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