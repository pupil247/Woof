#pragma once

#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ioMapping.h"
#include "CamHandler.h"
#include "M5Core2.h"
#include "WifiHandler.h"
#include "movementHandler.h"

using namespace ioMapping;

class ApplicationComposer {
private:
    static ApplicationComposer* my_app;
    ApplicationComposer(){
        
    }
    ~ApplicationComposer(){
        delete my_app;
    }
    ApplicationComposer(const ApplicationComposer&)=default;

    //private functions
    esp_err_t hardwareSetup();

    //Tasks
    CamHandler camHandler;
    WifiHandler wifiHandler;
    MovementHandler movementHandler;
    
    
public:
    static ApplicationComposer* getInstance(){
        if (my_app == NULL)
            my_app = new ApplicationComposer();
        return my_app;
    }
    esp_err_t init();
    esp_err_t loop();

};


