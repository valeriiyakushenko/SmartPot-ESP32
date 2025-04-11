#include <smart_pot.h>

Api api("https://example/api");

void setup() {
    setupSmartPot();  // Initialize all components
}

void loop() {
    displayClear();      // Clear display buffer

    switch (currentPage) {
        case 0:  // Time HH:MM
            displayDrawCentered(getTimeHM(), 2, 12);
            break;

        case 1:  // Temperature
            displayDrawCentered(getTemperature(), 2, 4);
            displayDrawCentered("Temperature", 1, 24);
            break;

        case 2:  // Get Api
            JsonDocument data = api.getData();
            String value = api.getString(data, "value");
    
            displayDrawCentered(value.c_str(), 1, 14);
            break;

        // Add more cases as needed
    }

	displayUpdate();
}