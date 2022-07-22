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
// MQx 	  	  mq3("mq3-alcohol       ", DEFAULT_POLLING_INTERVAL, 0);
// MQx 	  	  mq4("mq4-methane       ", DEFAULT_POLLING_INTERVAL, 1);
// MQx 	  	  mq7("mq7-co2           ", DEFAULT_POLLING_INTERVAL, 2);
// MQx 	  	  mq8("mq8-hydrogen      ", DEFAULT_POLLING_INTERVAL, 3);
// MQx 	 	  mq9("mq9-co            ", DEFAULT_POLLING_INTERVAL, 4);
// SHT40 	   sht40("sht40-temp-hum    ", DEFAULT_POLLING_INTERVAL, -1);
// SCD41 	   scd41("scd41-co2-temp-hum", DEFAULT_POLLING_INTERVAL, -1);
// IPC101xx ipc101xx("ipc101xx-temp-pres", DEFAULT_POLLING_INTERVAL, -1);
DS18B20	 ds18b20("ds18b20-temp      ", DEFAULT_POLLING_INTERVAL, 2);

void setup() 
{
	Serial.begin(9600);

	// mq3.begin();
	// mq4.begin();
	// mq7.begin();
	// mq8.begin();
	// mq9.begin();
	// sht40.begin();
	// scd41.begin();
	// ipc101xx.begin();
	ds18b20.begin();

	// Wait to allow for sensors to take an initial reading
	delay(DEFAULT_POLLING_INTERVAL);
}	

void loop() 
{
	unsigned long currentTimeMs = millis();

	// mq3.FSM(currentTimeMs);
	// mq4.FSM(currentTimeMs);
	// mq7.FSM(currentTimeMs);
	// mq8.FSM(currentTimeMs);
	// mq9.FSM(currentTimeMs);
	// sht40.FSM(currentTimeMs);
	// scd41.FSM(currentTimeMs);
	// ipc101xx.FSM(currentTimeMs);
	ds18b20.FSM(currentTimeMs);
}