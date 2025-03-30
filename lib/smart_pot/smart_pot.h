#pragma once

#ifndef SMART_POT_H
#define SMART_POT_H

#include <Arduino.h>
#include <ezTime.h>
#include <WiFiManager.h>
#include <DHT.h>

#include <display.h>
#include <config.h>
#include "../../src/constants.h"
#include <api.h>

extern DHT dht;
extern Display display;
extern Config config;
extern Timezone timeZone;
extern WiFiManager wifiManager;

extern int currentPage;
extern bool wifiConfigured;
extern volatile bool buttonPressed;

void setupSmartPot();
void handlePotControls();
const char* getTimeHM();
const char* getTimeHMS();
const char* getTemperature();
const char* getHumidity();
void IRAM_ATTR handleButtonPress();

#endif