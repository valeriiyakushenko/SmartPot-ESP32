#ifndef API_H
#define API_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <config.h>

class Api {
private:
    String baseUrl;
    String login;
    String password;
    JsonDocument lastJsonDocument;
    bool useAuth;
    unsigned long lastApiUpdateTime = 0;
    static const uint16_t HTTP_TIMEOUT_MS = 10000;

public:
    Api(const String& url);
    Api(const String& url, const String& user, const String& pass);

    JsonDocument getData();
    int getInt(const JsonDocument& doc, const String& key) const;
    String getString(const JsonDocument& doc, const String& key) const;
    bool isError() const;
};

#endif