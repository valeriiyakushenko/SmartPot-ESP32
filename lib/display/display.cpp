#include <display.h>

int screen_width = SCREEN_WIDTH;
int screen_height = SCREEN_HEIGHT;

DISPLAY_TYPE display(screen_width, screen_height, &Wire, OLED_RESET);

void initDisplay() {
    if (SCREEN_DRIVER == 1306) {
        display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    } else if (SCREEN_DRIVER == 1106){
        display.begin(SCREEN_ADDRESS, true);
    }
}

void displayDrawCentered(const char* text, int textSize, int y) {
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    
    display.setTextSize(textSize);
    display.setTextColor(TEXT_COLOR);
    display.getTextBounds(text, 0, y, &x1, &y1, &textWidth, &textHeight);
        
    int x = (screen_width - textWidth) / 2;
    display.setCursor(x, y);
    display.println(text);
}

void displayDraw(const char* text, int textSize, int x, int y) {
    display.setTextSize(textSize);
    display.setTextColor(TEXT_COLOR);
    display.setCursor(x, y);
    display.println(text);
}

void displayClear() {
    display.clearDisplay();}

void displayUpdate() {
    display.display();
}