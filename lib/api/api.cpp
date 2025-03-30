#include "api.h"

Api::Api(const String& url) : baseUrl(url), useAuth(false) {}

Api::Api(const String& url, const String& user, const String& pass) 
    : baseUrl(url), login(user), password(pass), useAuth(true) {}

JsonDocument Api::getData() {
    if (millis() - lastApiUpdateTime >= API_UPDATE_INTERVAL) {
        lastApiUpdateTime = millis();
        HTTPClient http;
        JsonDocument doc;
        
        String fullUrl = baseUrl;
        http.begin(fullUrl);
        
        if (useAuth) {
            http.setAuthorization(login.c_str(), password.c_str());
        }
    
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            deserializeJson(doc, payload);
        } else {
            Serial.print("HTTP request failed, error: ");
            Serial.println(httpCode);
        }
        http.end();

        lastJsonDocument = doc;
        return doc;
    }
    return lastJsonDocument;
}

int Api::getInt(const JsonDocument& doc, const String& key) {
    if (doc[key].is<int>()) {
        return doc[key].as<int>();
    }
    return 0;
}

String Api::getString(const JsonDocument& doc, const String& key) {
    if (doc[key].is<const char*>()) {
        return doc[key].as<String>();
    }
    return String("");
}