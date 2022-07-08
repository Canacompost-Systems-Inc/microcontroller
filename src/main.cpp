#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include "Boards/MQx/MQx.hpp"
#include "Boards/SHT40/SHT40.hpp"
#include "Boards/SCD41/SCD41.hpp"

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;

// ----- OBJECTS ----- //
// Linespacing formatted for pretty printing in debug
MQx 	mq3("\nmq3-alcohol       ", 0, DEFAULT_POLLING_INTERVAL);
MQx 	  mq4("mq4-methane       ", 1, DEFAULT_POLLING_INTERVAL);
MQx 	  mq7("mq7-co2           ", 2, DEFAULT_POLLING_INTERVAL);
MQx 	  mq8("mq8-hydrogen      ", 3, DEFAULT_POLLING_INTERVAL);
MQx 	  mq9("mq9-co            ", 4, DEFAULT_POLLING_INTERVAL);
SHT40 	sht40("sht40-temp-hum    ", -1, DEFAULT_POLLING_INTERVAL);
SCD41 	scd41("scd41-co2-temp-hum", -1, DEFAULT_POLLING_INTERVAL);

void setup() 
{
	Serial.begin(9600);

	mq3.begin();
	mq4.begin();
	mq7.begin();
	mq8.begin();
	mq9.begin();
	sht40.begin();
	scd41.begin();

	// Wait to allow for sensors to take an initial reading
	delay(DEFAULT_POLLING_INTERVAL);
}	

void loop() 
{
	unsigned long currentTimeMs = millis();

	mq3.FSM(currentTimeMs);
	mq4.FSM(currentTimeMs);
	mq7.FSM(currentTimeMs);
	mq8.FSM(currentTimeMs);
	mq9.FSM(currentTimeMs);
	sht40.FSM(currentTimeMs);
	scd41.FSM(currentTimeMs);
}