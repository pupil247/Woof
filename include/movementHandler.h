#pragma once
#include "Arduino.h"
#include "ioMapping.h"
#include "Movement.h"
#include "Wheel.h"
#include "cmath.h"

using namespace ioMapping;

class MovementHandler{

private:
    static MovementHandler * pObjet;
    Motor * wheel1;
    Motor * wheel2;
    Motor * wheel3;
    Movement::motor_t motor1;
    Movement::motor_t motor2;
    Movement::motor_t motor3;
    Movement * movement;
    uint8_t angle;
    uint8_t magnitude;
    static void task();
    
public:
    
    MovementHandler(){
        wheel1 = new Wheel("wheel1", Motor::status_t::MOTOR_ON, 0, uint8_t(GPIO_NUM_27));
        wheel2 = new Wheel("wheel1", Motor::status_t::MOTOR_ON, 0, uint8_t(GPIO_NUM_19));
        wheel3 = new Wheel("wheel1", Motor::status_t::MOTOR_ON, 0, uint8_t(GPIO_NUM_17));
        motor1.motor = wheel1;
        motor1.weight = 0;
        motor2.motor = wheel2;
        motor2.weight = 0;
        motor3.motor = wheel3;
        motor3.weight = 0;
        std::vector<Movement::motor_t> motorList;
        motorList.push_back(motor1);
        motorList.push_back(motor2);
        motorList.push_back(motor3);
        movement = new Movement(motorList);
    };

    move(uint16_t angle, uint16_t steps, uint8_t speed);
    turn(uint16_t steps);
    moveTurning(uint16_t angle, uint16_t steps, uint8_t speed, turnIntensity);
    ~MovementHandler(){
        delete movement;
        delete wheel1;
        delete wheel2;
        delete wheel3;
    };
    void start();
};
