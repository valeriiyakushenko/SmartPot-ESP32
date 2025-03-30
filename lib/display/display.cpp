#include <display.h>

Display::Display(int width, int height) : display(width, height, &Wire, OLED_RESET) {
    screen_width = width;
    screen_height = height;
}

bool Display::begin() {
    return display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.stopscroll();
}

void Display::drawCentered(const char* text, int textSize, int y) {
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    
    display.stopscroll();
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.getTextBounds(text, 0, y, &x1, &y1, &textWidth, &textHeight);
        
    int x = (screen_width - textWidth) / 2;
    display.setCursor(x, y);
    display.println(text);
}

void Display::draw(const char* text, int textSize, int x, int y) {
    display.stopscroll();
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(text);
}

void Display::clear() {
    display.clearDisplay();
    display.stopscroll();
}

void Display::update() {
    display.display();
}