#ifndef SMART_POT_H
#define SMART_POT_H

#include <DHT.h>
#include <ezTime.h>
#include <Arduino.h>
#include <WiFiManager.h>

#include <../../src/constants.h>
#include <api.h>
#include <config.h>
#include <display.h>
#include <encoder.h>

void setupSmartPot();
const char* getTimeHM();
const char* getTimeHMS();
const char* getTemperature();
const char* getHumidity();

#endif