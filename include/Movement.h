#pragma once

#include "Arduino.h"
#include <vector>
#include "Motor.h"

class Movement {
    public:
        struct motor_t{
            Motor * motor;
            uint8_t weight;
        };
        
        Movement(std::vector<motor_t> motorList) : motors(motorList){
        }
        ~Movement(){

        }
        esp_err_t setWeight(uint8_t index, uint8_t weight) {
            if(motors.size() <= index)
                return ESP_ERR_INVALID_ARG;
            motors[index].weight = weight;
        }
        uint8_t getWeight(uint8_t index){
            return motors[index].weight;
        }
        
        esp_err_t pidCompute(){
            for(auto motor : motors){
                motor.motor->setLevel(motor.weight);
            }
        }
    private:
        std::vector<motor_t> motors;
        

};