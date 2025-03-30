# SmartPot-ESP32 🌿💻

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

An intelligent plant monitoring system built on ESP32 with customizable display pages, environmental sensing, and WiFi configuration.

## Features ✨

- **Multi-page Display System** - Easily customizable display pages
- **Environmental Monitoring**:
  - 🌡️/💧 Temperature/Humidity sensor (DHT)
  - 🌱 Soil moisture measurement (Hydrometer)
- **Intuitive Controls**:
  - Rotary encoder for navigation
  - Tactile button for selection
- **Smart Connectivity**:
  - WiFi configuration via Access Point
  - API data integration
- **Modular Architecture** - Clean, maintainable code structure

## Hardware Requirements 🛠️

- ESP32 development board
- I2C OLED Display (128x32) or (128x64)
- DHT Temperature/Humidity sensor
- Soil moisture sensor
- Encoder with push button

## Getting Started 🚀

1. **Clone the repository**:
   ```bash
   git clone https://github.com/valeriiyakushenko/SmartPot-ESP32.git
   cd SmartPot-ESP32
   ```

2. **PlatformIO Setup**:
   - Install [PlatformIO IDE](https://platformio.org/platformio-ide)
   - Open the project folder
   - PlatformIO will automatically install dependencies

3. **Configure Settings**:
    Edit `constants.h` to match your hardware configuration:
    ```cpp
    // Screen settings
    #define SCREEN_WIDTH 128
    #define SCREEN_HEIGHT 32
    #define PAGES_COUNT 2 // Update based on your pages -1

    // Control settings
    #define BUTTON_PIN 4
    #define BUTTON_DEBOUNCE_DELAY  250

    // Api settings
    #define API_UPDATE_INTERVAL = 2500;

    // Sensors settings
    #define DHT_PIN 33
    #define DHT_TYPE DHT22 // or DHT11
    #define HYDROMETER_PIN 32

    // Time settings
    #define TIME_ZONE "America/Toronto"
    ```

4. **Upload to ESP32**:
   - Connect your ESP32 via USB
   - Click "Upload" in PlatformIO

## Display Page Examples 🖥️

The modular display system allows endless combinations of data presentation. Below are practical implementations:

### Main.cpp Example
```cpp
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
```

Always ensure PAGES_COUNT in `constants.h` exactly matches the number of case statements in your switch block.
```cpp
#define PAGES_COUNT 2 // Update based on your pages -1
```

### Basic Time Displays
```cpp
case 0:  // HH:MM
    display.drawCentered(getTimeHM(), 2, 12);
    break;

case 1:  // HH:MM:SS 
    display.drawCentered(getTimeHMS(), 2, 12);
    break;
```

### Environmental Monitoring
```cpp
case 2:  // Temperature / Humidity combo
    display.drawCentered(getTemperature(), 1, 4);
    display.drawCentered(getHumidity(), 1, 14);
    break;

case 3:  // Soil moisture
    display.drawCentered(getMoisture(), 2, 4);
    display.drawCentered("Moisture", 1, 24);
    break;
```

### API Data Visualizations
```cpp
Api api("https://example/api");

case 4:  // Get Api
    JsonDocument data = api.getData();
    String value = api.getString(data, "value");
    
    display.drawCentered(value.c_str(), 1, 14);
    break;
```

## WiFi Configuration 📶

The SmartPot creates a configuration Access Point when no WiFi credentials are stored:

1. Power on the device  
2. Connect to the "SetUp" WiFi network
3. A setup page will open automatically *(if it doesn't, manually go to `http://192.168.4.1`)*
4. Enter your WiFi credentials
5. The device will save settings and reboot

## API Integration 🌐

The project includes helper functions for API requests. Example usage:

```cpp
Api api("https://example/api"); // Api example("https://example/api", "login", "password");

JsonDocument data = api.getData();
int num = api.getInt(data, "num");
String value = api.getString(data, "value");
```

## Contributing 🤝

Contributions are welcome! Please follow these guidelines:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License 📄

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.