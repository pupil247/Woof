#include "ApplicationComposer.h"

esp_err_t ApplicationComposer::init(){
    Serial.begin(115200);
    M5.begin();
    M5.Axp.SetSpkEnable(1);
    M5.Lcd.fillScreen(RED);
    delay(1000);
    M5.Lcd.fillScreen(BLUE);
    camHandler.start();
    screenHandler.start();
    
    return ESP_OK;
}

esp_err_t ApplicationComposer::loop(){
    
    int x = 0;
    int y = 0;
    
    
    M5.update();
    if (M5.BtnA.wasReleased()) {  
        // Implement your shutdown logic here
        M5.shutdown();  // Power off M5Stack
    }
    return ESP_OK;
}

esp_err_t ApplicationComposer::hardwareSetup(){
    //pinMode(LED_ONBOARD, OUTPUT);
    return ESP_OK;
}

ApplicationComposer * ApplicationComposer::my_app = NULL;
