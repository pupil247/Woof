#include "ApplicationComposer.h"

esp_err_t ApplicationComposer::init(){

    camHandler.start();
    return ESP_OK;
}

esp_err_t ApplicationComposer::loop(){
    //main task loop

    return ESP_OK;
}

esp_err_t ApplicationComposer::hardwareSetup(){
    pinMode(LED_ONBOARD, OUTPUT);
    return ESP_OK;
}

ApplicationComposer * ApplicationComposer::my_app = NULL;
