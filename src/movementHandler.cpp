#include "movementHandler.h"
    
void MovementHandler::start(){
    xTaskCreatePinnedToCore( (TaskFunction_t)task,    "Task movement",    5000,      NULL,    4,    NULL,    1);
}

void MovementHandler::task(){
    while(1){
        
        move(45,)
        
        
    }
    
}
   

MovementHandler::move(uint16_t angle, uint16_t steps, uint8_t speed){
    if(angle > 360)
        return;
    if(angle > 180)
        angle = (angle - 180) * -1;
    

    //movement.setWeight(0,cos(180 - 45 -angle) * speed);
    //movement.setWeight(1, (int)Math.Round(Math.Sqrt(Math.Pow(cos(angle - 45), 2) + Math)));
    //movement.setWeight(2, * speed);

}
MovementHandler::turn(uint16_t steps){
}
MovementHandler::moveTurning(){

}
MovementHandler* MovementHandler::pObjet = nullptr;