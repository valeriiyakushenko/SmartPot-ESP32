#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Preferences.h>
#include <../../src/constants.h>

bool configGetBool(const char* key, bool defaultValue = false);
int configGetInt(const char* key, int defaultValue = 0);
float configGetFloat(const char* key, float defaultValue = 0.0f);
String configGetString(const char* key, const String& defaultValue = "");

void configPutBool(const char* key, bool value);
void configPutInt(const char* key, int value);
void configPutFloat(const char* key, float value);
void configPutString(const char* key, const String& value);

void configRemove(const char* key);
void configClear();

#endif