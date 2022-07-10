#include "DS18B20.hpp"


void DS18B20::read()
{
    float temperature;

    ds18b20.requestTemperatures(); 
    temperature = ds18b20.getTempCByIndex(0);

    clearData();
    data[0] = temperature;
    valid[0] = true;
}   

void DS18B20::begin()
{
    ds18b20.begin();
}