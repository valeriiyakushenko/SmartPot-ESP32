#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

extern unsigned long lastApiUpdateTime;
extern unsigned long lastButtonPressTime;

class Config {
private:
    Preferences preferences;
    const char* namespaceName;

public:
    Config(const char* nameSpace = "Storage");
    ~Config();

    bool getBool(const char* key, bool defaultValue = false);
    int getInt(const char* key, int defaultValue = 0);
    float getFloat(const char* key, float defaultValue = 0.0f);
    String getString(const char* key, const String& defaultValue = "");

    void putBool(const char* key, bool value);
    void putInt(const char* key, int value);
    void putFloat(const char* key, float value);
    void putString(const char* key, const String& value);

    void remove(const char* key);
    void clear();
};

#endif