
#include "CamHandler.h"
    
void CamHandler::start(){
    xTaskCreatePinnedToCore( (TaskFunction_t)task,    "Task cam",    5000,      NULL,    4,    NULL,    1);
}

void CamHandler::task(){
    while(1){
        //digitalWrite(LED_ONBOARD, HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    
}
   


CamHandler* CamHandler::pObjet = nullptr;