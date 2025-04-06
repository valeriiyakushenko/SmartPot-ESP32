#include <display.h>

Display::Display(int width, int height) : display(width, height, &Wire, OLED_RESET) {
    screen_width = width;
    screen_height = height;
}

bool Display::begin() {
    if (SCREEN_DRIVER == 1306) {
        return display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    } else if (SCREEN_DRIVER == 1106){
        return display.begin(SCREEN_ADDRESS, true);
    }
}

void Display::drawCentered(const char* text, int textSize, int y) {
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    
    display.setTextSize(textSize);
    display.setTextColor(TEXT_COLOR);
    display.getTextBounds(text, 0, y, &x1, &y1, &textWidth, &textHeight);
        
    int x = (screen_width - textWidth) / 2;
    display.setCursor(x, y);
    display.println(text);
}

void Display::draw(const char* text, int textSize, int x, int y) {
    display.setTextSize(textSize);
    display.setTextColor(TEXT_COLOR);
    display.setCursor(x, y);
    display.println(text);
}

void Display::clear() {
    display.clearDisplay();}

void Display::update() {
    display.display();
}