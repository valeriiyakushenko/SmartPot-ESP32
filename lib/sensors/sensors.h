#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>
#include <config.h>

void initSensors();
const char* getTemperature();
const char* getHumidity();

#endif