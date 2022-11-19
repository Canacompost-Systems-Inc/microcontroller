#include "IPC10100.hpp"


Array<float> IPC10100::read() {
	Array<float> reading;

	if (ipc10100.dataReady()) {
    // Read and output measured temperature in Fahrenheit and pressure in Pascal.
    reading.insert(ipc10100.getTemperatureC());
    reading.insert(ipc10100.getPressurePa());

    // start the next measurement cycle.
    ipc10100.measureStart(ipc10100.VERY_ACCURATE);
  }

	return reading;
}

void IPC10100::begin() {
	// TODO: Handle error cases
	if (!ipc10100.begin()) {
	  Serial.println("Mikroe-3328 baro sensor failed to connect");
	}

	if (!ipc10100.isConnected()) {
		Serial.println("Mikroe-3328 baro sensor failed to connect");
	} 
}