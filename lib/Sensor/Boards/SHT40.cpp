#include "SHT40.hpp"


float SHT40::read()
{
    if(mode == TEMP)
    {
        float temperature = sht40.getTemperature(PRECISION_HIGH);
        if(temperature == MODE_ERR)
        {
            Serial.println("Incorrect mode configuration to get temperature");
        }

        return temperature;
    }
    else if(mode == HUM)
    {
        float humidity = sht40.getHumidity(PRECISION_HIGH);
        if(humidity == MODE_ERR)
        {
            Serial.println("The mode for getting humidity was misconfigured");
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

        return humidity;
    }
}

SHT40::SHT40(Mode initialMode, unsigned long initialPollingInterval): Sensor(initialPollingInterval), sht40(SHT40_AD1B_IIC_ADDR) 
{
    mode = initialMode;
};

void SHT40::begin()
{
    uint32_t id = 0;
    
    // TODO: add timeout case to remove inf loop
	while((id = sht40.getDeviceID()) == 0)
    {
		Serial.println("ID retrieval error, please check whether the device is connected correctly!!!");
		delay(1000);
    }
}