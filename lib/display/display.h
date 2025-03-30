#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1


class Display {
public:
    Display(int width, int height);
    bool begin();
    void drawCentered(const char* text, int textSize, int y);
    void draw(const char* text, int textSize, int x, int y);
    void clear();
    void update();

private:
    int screen_height;
    int screen_width;
    Adafruit_SSD1306 display;
};

#endif