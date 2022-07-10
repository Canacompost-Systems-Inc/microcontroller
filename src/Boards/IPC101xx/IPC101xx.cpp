#include "IPC101xx.hpp"


void IPC101xx::read()
{
	float temperature = data[0];
	float pressure = data[1];

	if (ipc101xx.dataReady()) 
	{
		// Read and output measured temperature in Fahrenheit and pressure in Pascal.
		temperature = ipc101xx.getTemperatureC();
		pressure = ipc101xx.getPressurePa();

		// start the next measurement cycle.
		ipc101xx.measureStart(ipc101xx.VERY_ACCURATE);
  	}

	clearData();
	data[0] = temperature;
	data[1] = pressure;
	valid[0] = true;
	valid[1] = true;
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