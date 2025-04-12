#include <wifi_setup.h>

WiFiManager wifiManager;

void initWiFi() {
    if (isEncoderButtonPressed || !configGetBool("WiFi", false)) {
        displayClear();

        if (SCREEN_HEIGHT == 32) {
            displayDrawCentered("Configure WiFi...", 1, 4);  
            displayDrawCentered("Connect to: SetUp", 1, 18);
        } else {
            displayDrawCentered("Configure WiFi...", 1, 4);  
            displayDrawCentered("Connect to: SetUp", 1, 18);
        }

        displayUpdate();
        configClear();
        currentPage = 0;

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
        configPutBool("WiFi", true);
        displayClear();

        if (SCREEN_HEIGHT == 32) {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Connected!", 1, 18);
        } else {
            displayDrawCentered("WiFi", 1, 4);
            displayDrawCentered("Connected!", 1, 18);
        }
        
        displayUpdate();
    }
}