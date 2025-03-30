#ifndef API_H
#define API_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "../../src/constants.h"
#include "../config/config.h"

class Api {
private:
    String baseUrl;
    String login;
    String password;
    JsonDocument lastJsonDocument;
    bool useAuth;

public:
    Api(const String& url);
    Api(const String& url, const String& user, const String& pass);

    JsonDocument getData();
    int getInt(const JsonDocument& doc, const String& key);
    String getString(const JsonDocument& doc, const String& key);
};

#endif