#include <sensors.h>

DHT dht(DHT_PIN, DHT_TYPE);

void initSensors() {
    dht.begin();
}

const char* getTemperature() {
    static char buffer[8];
    float t = dht.readTemperature();
    
    if (isnan(t)) {
        return "Error";
    } else {
        snprintf(buffer, sizeof(buffer), "%.1f", t);
        return buffer;
    }
}

const char* getHumidity() {
    static char buffer[8];
    float h = dht.readHumidity();
    
    if (isnan(h)) {
        return "Error";
    } else {
        snprintf(buffer, sizeof(buffer), "%.1f", h);
        return buffer;
    }
}