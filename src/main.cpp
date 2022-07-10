#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Arduino.h>
#include "Boards/MQx/MQx.hpp"
#include "Boards/SHT40/SHT40.hpp"
#include "Boards/SCD41/SCD41.hpp"
#include "Boards/IPC101xx/IPC101xx.hpp"
#include "Boards/DS18B20/DS18B20.hpp"

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;

// ----- OBJECTS ----- //
// Linespacing formatted for pretty printing in debug
// TODO: put objects in array?
// MQx 	  	  mq3("mq3-alcohol       ", 0, DEFAULT_POLLING_INTERVAL, false);
// MQx 	  	  mq4("mq4-methane       ", 1, DEFAULT_POLLING_INTERVAL, false);
// MQx 	  	  mq7("mq7-co2           ", 2, DEFAULT_POLLING_INTERVAL, false);
// MQx 	  	  mq8("mq8-hydrogen      ", 3, DEFAULT_POLLING_INTERVAL, false);
// MQx 	 	  mq9("mq9-co            ", 4, DEFAULT_POLLING_INTERVAL, false);

SHT40 	  sht40("\nsht40-temp-hum    ", -1, DEFAULT_POLLING_INTERVAL, true);
SCD41 		scd41("scd41-co2-temp-hum", -1, DEFAULT_POLLING_INTERVAL, true);
IPC101xx ipc101xx("ipc101xx-temp-pres", -1, DEFAULT_POLLING_INTERVAL, true);
DS18B20	  ds18b20("ds18b20-temp      ", 2, DEFAULT_POLLING_INTERVAL, true);

void setup() 
{
	Serial.begin(9600);

	sht40.begin();
	scd41.begin();
	ipc101xx.begin();
	ds18b20.begin();

	// Wait to allow for sensors to take an initial reading
	delay(DEFAULT_POLLING_INTERVAL);
}	

void loop() 
{
	unsigned long currentTimeMs = millis();

	sht40.FSM(currentTimeMs);
	scd41.FSM(currentTimeMs);
	ipc101xx.FSM(currentTimeMs);
	ds18b20.FSM(currentTimeMs);
}