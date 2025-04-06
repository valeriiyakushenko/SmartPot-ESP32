#include <config.h>

Preferences preferences;
const char* nameSpace = "Storage";

bool configGetBool(const char* key, bool defaultValue) {
    preferences.begin(nameSpace, true);
    bool value = preferences.getBool(key, defaultValue);
    preferences.end();
    return value;
}

int configGetInt(const char* key, int defaultValue) {
    preferences.begin(nameSpace, true);
    int value = preferences.getInt(key, defaultValue);
    preferences.end();
    return value;
}

float configGetFloat(const char* key, float defaultValue) {
    preferences.begin(nameSpace, true);
    float value = preferences.getFloat(key, defaultValue);
    preferences.end();
    return value;
}

String configGetString(const char* key, const String& defaultValue) {
    preferences.begin(nameSpace, true);
    String result = preferences.getString(key, defaultValue.c_str());
    preferences.end();
    return result;
}

void configPutBool(const char* key, bool value) {
    preferences.begin(nameSpace, false);
    preferences.putBool(key, value);
    preferences.end();
}

void configPutInt(const char* key, int value) {
    preferences.begin(nameSpace, false);
    preferences.putInt(key, value);
    preferences.end();
}

void configPutFloat(const char* key, float value) {
    preferences.begin(nameSpace, false);
    preferences.putFloat(key, value);
    preferences.end();
}

void configPutString(const char* key, const String& value) {
    preferences.begin(nameSpace, false);
    preferences.putString(key, value.c_str());
    preferences.end();
}

void configRemove(const char* key) {
    preferences.begin(nameSpace, false);
    preferences.remove(key);
    preferences.end();
}

void configClear() {
    preferences.begin(nameSpace, false);
    preferences.clear();
    preferences.end();
}