#include <smart_pot.h>

Display display(SCREEN_WIDTH, SCREEN_HEIGHT);
Config config;
Timezone timeZone;
WiFiManager wifiManager;
DHT dht(DHT_PIN, DHT_TYPE);

int currentPage = 0;
bool wifiConfigured = false;

int currentClkState;
int lastClkState = HIGH;

void setupSmartPot() {
    display.begin();
    dht.begin();
    
    wifiConfigured = config.getBool("WiFi", false);
    currentPage = config.getInt("Page", 0);

    pinMode(CLK_PIN, INPUT_PULLUP);
    pinMode(DT_PIN, INPUT_PULLUP);
    pinMode(SW_PIN, INPUT_PULLUP);
  
    if (digitalRead(SW_PIN) == LOW || wifiConfigured == false) {
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
        config.clear();
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
        config.putBool("WiFi", wifiConfigured);
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

void handlePotControls() {
    currentClkState = digitalRead(CLK_PIN);

    if (currentClkState != lastClkState && currentClkState == HIGH) {
        if (digitalRead(DT_PIN) == HIGH) {
            if (currentPage >= PAGES_COUNT) {
                currentPage = 0;
            } else {
                currentPage++;
            }
        } else {
            if (currentPage <= 0) {
                currentPage = PAGES_COUNT;
            } else {
                currentPage--;
            }
        }
        config.putInt("Page", currentPage);
    }

    lastClkState = currentClkState;
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