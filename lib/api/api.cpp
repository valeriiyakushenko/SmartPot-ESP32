#include <api.h>

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
        
        http.setTimeout(HTTP_TIMEOUT_MS);
        
        if (useAuth) {
            http.setAuthorization(login.c_str(), password.c_str());
        }
    
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            DeserializationError error = deserializeJson(doc, payload);
            
            if (error) {
                http.end();
                return lastJsonDocument;
            }
        } else {
            http.end();
            return lastJsonDocument;
        }
        http.end();

        lastJsonDocument = doc;
    }
    return lastJsonDocument;
}

int Api::getInt(const JsonDocument& doc, const String& key) const {
    if (!doc[key].is<int>()) {
        return 0;
    }
    return doc[key].as<int>();
}

String Api::getString(const JsonDocument& doc, const String& key) const {
    if (!doc[key].is<const char*>()) {
        return String();
    }
    return doc[key].as<String>();
}

bool Api::isError() const {
    return lastJsonDocument.isNull();
}