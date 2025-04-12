#include <encoder.h>

EncButton encoder(CLK_PIN, DT_PIN, SW_PIN);
TaskHandle_t encoderTaskHandle = nullptr;

int currentPage = 0;
bool isEncoderButtonPressed = false;

void handleEncoder(void *pvParameters) {
    for(;;) {
        encoder.tick();
        
        isEncoderButtonPressed = (digitalRead(SW_PIN) == LOW);

        if (encoder.turn()) {
            currentPage += encoder.dir(); 

            if (currentPage > PAGES_COUNT) currentPage = 0;
            if (currentPage < 0) currentPage = PAGES_COUNT;
        }

        configPutInt("Page", currentPage);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}


void initEncoder() {
    currentPage = configGetInt("Page", 0);
    isEncoderButtonPressed = (digitalRead(SW_PIN) == LOW);

    xTaskCreatePinnedToCore(
        handleEncoder,
        "EncoderTask",
        2048,
        nullptr,
        1,
        &encoderTaskHandle,
        0
    );
}