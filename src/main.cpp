#include <smart_pot.h>

Api api("https://example/api");

void setup() {
    setupSmartPot();  // Initialize all components
}

void loop() {
    handlePotControls();  // Handle encoder/button inputs
    display.clear();      // Clear display buffer

    switch (currentPage) {
        case 0:  // Time HH:MM
            display.drawCentered(getTimeHM(), 2, 12);
            break;

        case 1:  // Temperature
            display.drawCentered(getTemperature(), 2, 4);
            display.drawCentered("Temperature", 1, 24);
            break;

        case 2:  // Get Api
            JsonDocument data = api.getData();
            String value = api.getString(data, "value");
    
            display.drawCentered(value.c_str(), 1, 14);
            break;

        // Add more cases as needed
    }

	display.update();
}