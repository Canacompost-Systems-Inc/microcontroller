#include "SHT40.hpp"


void SHT40::read()
{
    float temperature = sht40.getTemperature(PRECISION_HIGH);
    if(temperature == MODE_ERR)
    {
        Serial.println("Incorrect mode configuration to get temperature");
        return;
    }

    float humidity = sht40.getHumidity(PRECISION_HIGH);
    if(humidity == MODE_ERR)
    {
        Serial.println("The mode for getting humidity was misconfigured");
        return;
    } 

    if(humidity > 80)
    {
        /** humidity sensor modes
         * POWER_CONSUMPTION_H_HEATER_1S        activate highest heater power & high precis. meas. for 1s 
         * POWER_CONSUMPTION_H_HEATER_100MS     activate highest heater power & high precis. meas. for 0.1s
         * POWER_CONSUMPTION_M_HEATER_1S        activate medium heater power  & high precis. meas. for 1s 
         * POWER_CONSUMPTION_M_HEATER_100MS     activate medium heater power  & high precis. meas. for 0.1s 
         * POWER_CONSUMPTION_L_HEATER_1S        activate lowest heater power  & high precis. meas. for 1s 
         * POWER_CONSUMPTION_L_HEATER_100MS     activate lowest heater power  & high precis. meas. for 0.1s 
         */
        sht40.enHeater(POWER_CONSUMPTION_H_HEATER_1S);
    }

    clearData();
    data[0] = temperature;
    data[1] = humidity;
    valid[0] = true;
    valid[1] = true;
}

void SHT40::begin()
{
    uint32_t id = 0;
    sht40.begin();
    
	while((id = sht40.getDeviceID()) == 0)
    {
		Serial.println("ID retrieval error, please check whether the device is connected correctly!!!");
		return;
    }
}
