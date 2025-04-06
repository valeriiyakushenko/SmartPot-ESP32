#include <smart_pot.h>

Display display(SCREEN_WIDTH, SCREEN_HEIGHT);
Timezone timeZone;
WiFiManager wifiManager;
DHT dht(DHT_PIN, DHT_TYPE);

bool wifiConfigured = false;

void setupSmartPot() {
    display.begin();
    dht.begin();
    initEncoder();

    wifiConfigured = configGetBool("WiFi", false);
  
    if (isEncoderButtonPressed() || wifiConfigured == false) {
        display.clear();
        if (SCREEN_HEIGHT == 32) {
            display.drawCentered("Configure WiFi...", 1, 4);  
            display.drawCentered("Connect to: SetUp", 1, 18);
        } else {
            display.drawCentered("Configure WiFi...", 1, 4);  
            display.drawCentered("Connect to: SetUp", 1, 18);
        }
        display.update();
        wifiConfigured = false;
        currentPage = 0;
        configClear();
        wifiManager.resetSettings();
        wifiManager.startConfigPortal("SetUp");
    } else {
        display.clear();
        if (SCREEN_HEIGHT == 32) {
            display.drawCentered("WiFi", 1, 4);
            display.drawCentered("Connecting...", 1, 18);
        } else {
            display.drawCentered("WiFi", 1, 4);
            display.drawCentered("Connecting...", 1, 18);
        }
        display.update();

    }
    
    if (!wifiManager.autoConnect()) {
        display.clear();
        if (SCREEN_HEIGHT == 32) {
            display.drawCentered("WiFi", 1, 4);
            display.drawCentered("Failed!", 1, 18);
        } else {
            display.drawCentered("WiFi", 1, 4);
            display.drawCentered("Failed!", 1, 18);
        }
        display.update();
        delay(2500);
        ESP.restart();

    } else {
        wifiConfigured = true;
        configPutBool("WiFi", wifiConfigured);
        display.clear();
        if (SCREEN_HEIGHT == 32) {
            display.drawCentered("WiFi", 1, 4);
            display.drawCentered("Connected!", 1, 18);
        } else {
            display.drawCentered("WiFi", 1, 4);
            display.drawCentered("Connected!", 1, 18);
        }
        display.update();

        waitForSync();
        timeZone.setLocation(F(TIME_ZONE));
    }
}

const char* getTimeHM() {
    static char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", timeZone.hour(), timeZone.minute());
    return buffer;
}

const char* getTimeHMS() {
    static char buffer[9];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", timeZone.hour(), timeZone.minute(), timeZone.second());
    return buffer;
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