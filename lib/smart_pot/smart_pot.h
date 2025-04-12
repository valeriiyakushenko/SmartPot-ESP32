#ifndef SMART_POT_H
#define SMART_POT_H

#include <api.h>
#include <config.h>
#include <ezTime.h>
#include <sensors.h>
#include <Arduino.h>
#include <display.h>
#include <encoder.h>
#include <WiFiManager.h>

void setupSmartPot();
const char* getTimeHM();
const char* getTimeHMS();

#endif