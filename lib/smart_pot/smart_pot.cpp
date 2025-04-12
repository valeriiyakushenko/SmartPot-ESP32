#include <smart_pot.h>

Timezone timeZone;
WiFiManager wifiManager;

bool wifiConfigured = false;

void setupSmartPot() {
    initDisplay();
    initEncoder();
    initSensors();

    wifiConfigured = configGetBool("WiFi", false);
  
    if (isEncoderButtonPressed() || wifiConfigured == false) {
        displayClear();
        if (SCREEN_HEIGHT == 32) {
            displayDrawCentered("Configure WiFi...", 1, 4);  
            displayDrawCentered("Connect to: SetUp", 1, 18);
        } else {
            displayDrawCentered("Configure WiFi...", 1, 4);  
            displayDrawCentered("Connect to: SetUp", 1, 18);
        }
        displayUpdate();
        wifiConfigured = false;
        currentPage = 0;
        configClear();
        wifiManager.resetSettings();
        wifiManager.startConfigPortal("SetUp");
    } else {
        displayClear();
        if (SCREEN_HEIGHT == 32) {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Connecting...", 1, 18);
        } else {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Connecting...", 1, 18);
        }
        displayUpdate();

    }
    
    if (!wifiManager.autoConnect()) {
        displayClear();
        if (SCREEN_HEIGHT == 32) {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Failed!", 1, 18);
        } else {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Failed!", 1, 18);
        }
        displayUpdate();
        delay(2500);
        ESP.restart();

    } else {
        wifiConfigured = true;
        configPutBool("WiFi", wifiConfigured);
        displayClear();
        if (SCREEN_HEIGHT == 32) {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Connected!", 1, 18);
        } else {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Connected!", 1, 18);
        }
        displayUpdate();

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