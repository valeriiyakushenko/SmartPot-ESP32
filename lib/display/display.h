#ifndef DISPLAY_H
#define DISPLAY_H

#include <config.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C 
#define OLED_RESET -1

#if SCREEN_DRIVER == 1306
    #define DISPLAY_TYPE Adafruit_SSD1306
    #define TEXT_COLOR SSD1306_WHITE
#elif SCREEN_DRIVER == 1106
    #define DISPLAY_TYPE Adafruit_SH1106G
    #define TEXT_COLOR SH110X_WHITE
#else
  #error "Unsupported display driver. Define SCREEN_DRIVER as either 1306 or 1106"
#endif

void initDisplay();
void displayDrawCentered(const char* text, int textSize, int y);
void displayDraw(const char* text, int textSize, int x, int y);
void displayClear();
void displayUpdate();

#endif