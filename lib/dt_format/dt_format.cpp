#include <dt_format.h>

Timezone timeZone;

void initRTC() {
    waitForSync();
    timeZone.setLocation(F(TIME_ZONE));
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