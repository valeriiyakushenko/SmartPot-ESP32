#include <smart_pot.h>

void setupSmartPot() {
    initDisplay();
    initEncoder();
    initSensors();
    initWiFi();
    initRTC();
}

