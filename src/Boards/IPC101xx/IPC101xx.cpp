#include "IPC101xx.hpp"


Array<float> IPC101xx::read()
{
	Array<float> reading;

	if (ipc101xx.dataReady()) 
	{
		// Read and output measured temperature in Fahrenheit and pressure in Pascal.
		reading.insert(ipc101xx.getTemperatureC());
		reading.insert(ipc101xx.getPressurePa());

		// start the next measurement cycle.
		ipc101xx.measureStart(ipc101xx.VERY_ACCURATE);
  	}

	return reading;
}

void IPC101xx::begin()
{
	// TODO: Handle error case
	if (!ipc101xx.begin()) 
    {
	  Serial.println("Mikroe-3328 baro sensor failed to connect");
	}

	if (!ipc101xx.isConnected()) 
    {
		Serial.println("Mikroe-3328 baro sensor failed to connect");
	} 
}