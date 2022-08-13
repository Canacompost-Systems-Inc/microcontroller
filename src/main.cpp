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
#include "Boards/IPC101xx/IPC101xx.hpp"
#include "Boards/DS18B20/DS18B20.hpp"

// ----- CONSTANTS ----- //
const unsigned long DEFAULT_POLLING_INTERVAL = 5000;

// ----- OBJECTS ----- //
// MQx 	  	  mq3("mq3-alcohol       ", DEFAULT_POLLING_INTERVAL, 0);
// MQx 	  	  mq4("mq4-methane       ", DEFAULT_POLLING_INTERVAL, 1);
// MQx 	  	  mq7("mq7-co2           ", DEFAULT_POLLING_INTERVAL, 2);
// MQx 	  	  mq8("mq8-hydrogen      ", DEFAULT_POLLING_INTERVAL, 3);
// MQx 	 	  mq9("mq9-co            ", DEFAULT_POLLING_INTERVAL, 4);
// IPC101xx ipc101xx("ipc101xx-temp-pres", DEFAULT_POLLING_INTERVAL, -1);
// DS18B20	  ds18b20("ds18b20-temp      ", DEFAULT_POLLING_INTERVAL, 2);
SHT40 	    sht40(0x00, DEFAULT_POLLING_INTERVAL, -1);
SCD41 	    scd41(0x10, DEFAULT_POLLING_INTERVAL, -1);

Array<Sensor*> sensors;
char buf[200];

void setup() 
{
	Serial.begin(9600);

	sensors.insert(&sht40);
	// sensors.insert(&scd41);

	for (int i = 0; i < sensors.getSize(); i++)
	{
		sensors.read(i)->begin();
	}

	// Wait to allow for sensors to take an initial reading
	delay(DEFAULT_POLLING_INTERVAL);
}

void loop() 
{
	unsigned long currentTimeMs = millis();

	for (int i = 0; i < sensors.getSize(); i++)
	{
		sensors.read(i)->FSM(currentTimeMs);
	}

	// Application Layer 
	if (Serial.available()) 
	{
		byte inByte = Serial.read();

		// 's' = state of sensors
		if (inByte == 0x73)
		{
			Serial.write(0x02); // STX: Start of text
			for (int i = 0; i < sensors.getSize(); i++)
			{
				sensors.read(i)->report();
			}
        	Serial.write(0x03); // ETX: End of text
		}
	}
}