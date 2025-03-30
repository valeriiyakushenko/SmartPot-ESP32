#include <config.h>

unsigned long lastApiUpdateTime = 0;
unsigned long lastButtonPressTime = 0;

Config::Config(const char* nameSpace) : namespaceName(nameSpace) {}

Config::~Config() {}

bool Config::getBool(const char* key, bool defaultValue) {
    preferences.begin(namespaceName, true);
    bool value = preferences.getBool(key, defaultValue);
    preferences.end();
    return value;
    
}

int Config::getInt(const char* key, int defaultValue) {
    preferences.begin(namespaceName, true);
    int value = preferences.getInt(key, defaultValue);
    preferences.end();
    return value;
}

float Config::getFloat(const char* key, float defaultValue) {
    preferences.begin(namespaceName, true);
    float value = preferences.getFloat(key, defaultValue);
    preferences.end();
    return value;
}

String Config::getString(const char* key, const String& defaultValue) {
    preferences.begin(namespaceName, true);
    String result = preferences.getString(key, defaultValue.c_str());
    preferences.end();
    return result;
}

void Config::putBool(const char* key, bool value) {
    preferences.begin(namespaceName, false);
    preferences.putBool(key, value);
    preferences.end();
}

void Config::putInt(const char* key, int value) {
    preferences.begin(namespaceName, false);
    preferences.putInt(key, value);
    preferences.end();
}

void Config::putFloat(const char* key, float value) {
    preferences.begin(namespaceName, false);
    preferences.putFloat(key, value);
    preferences.end();
}

void Config::putString(const char* key, const String& value) {
    preferences.begin(namespaceName, false);
    preferences.putString(key, value.c_str());
    preferences.end();
}

void Config::remove(const char* key) {
    preferences.begin(namespaceName, false);
    preferences.remove(key);
    preferences.end();
}

void Config::clear() {
    preferences.begin(namespaceName, false);
    preferences.clear();
    preferences.end();
}