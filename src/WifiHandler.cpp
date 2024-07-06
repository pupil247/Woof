#include "WifiHandler.h"
    
WifiHandler::WifiHandler(){
    ssid = "Loulou";
    password = "Loulou141295";
}
WifiHandler::~WifiHandler(){
    
}

void WifiHandler::start(){
    WiFi.begin(ssid.c_str(), password.c_str());
    xTaskCreatePinnedToCore( (TaskFunction_t)task,    "Task cam",    5000,      NULL,    4,    NULL,    1);
}

void WifiHandler::task(){
    while(1){
        while (WiFi.status() != WL_CONNECTED) {
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            Serial.println("Connecting to WiFi...");
        }   
        //reception

        //envoie des informations du robot a l'application
        Serial.println("Connected to WiFi");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    
}
   


WifiHandler* WifiHandler::pObjet = nullptr;