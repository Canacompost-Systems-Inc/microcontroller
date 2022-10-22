#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>
#include "Array.hpp"
#include "Boards/MQx/MQx.hpp"
#include "Boards/SHT40/SHT40.hpp"
#include "Boards/SCD41/SCD41.hpp"
#include "Boards/IPC10100/IPC10100.hpp"
#include "Boards/DS18B20/DS18B20.hpp"
#include "Boards/YFS201/YFS201.hpp"
#include "ControlUnit/ControlUnit.hpp"

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;
const unsigned long FAST_POLLING_INTERVAL = 1000;

// ----- OBJECTS ----- //
// Actuator Objects
Actuator valve0(0xE0, 0);

// Sensor Objects
SHT40 	    sht40(0xC0, DEFAULT_POLLING_INTERVAL, -1);
SCD41 	    scd41(0xC1, DEFAULT_POLLING_INTERVAL, -1);
IPC10100 ipc10100(0xC2, DEFAULT_POLLING_INTERVAL, -1);
DS18B20	  ds18b20(0xC3, DEFAULT_POLLING_INTERVAL, 2);
YFS201	   yfs201(0xC4, FAST_POLLING_INTERVAL, 3);

Array<Sensor*> sensors;
Array<Actuator*> actuators;
ControlUnit controller;

void YSF201InterruptHandler() {
	yfs201.pulse();
}

void setupActuators() {
  actuators.insert(&valve0);

	for (int i = 0; i < actuators.getSize(); i++) {
		actuators.read(i)->begin();
	}
}

void setupSensors() {
	// sensors.insert(&sht40);
	// sensors.insert(&scd41);
	sensors.insert(&yfs201);

	for (int i = 0; i < sensors.getSize(); i++) {
		sensors.read(i)->begin();
	}

	// Attach interrupts
	attachInterrupt(digitalPinToInterrupt(yfs201.getPin()), YSF201InterruptHandler, RISING);

	// Wait to allow for sensors to setup
	delay(DEFAULT_POLLING_INTERVAL);
}

//  Runs every time serial connection is established OR when arduino is powered on.
void setup() {
	Serial.begin(9600);
	// setupActuators();
	setupSensors();
	controller.begin(actuators, sensors);
}

// Runs every clock cycle
void loop() {
	controller.loop();
}