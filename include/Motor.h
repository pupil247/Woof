#pragma once

#include "Arduino.h"

class Motor{
    public:
        enum status_t{
            MOTOR_ON,
            MOTOR_OFF
        };   
    protected:
        
        enum direction_t{
            FORWARD,
            BACKWARD
        };
        std::string _name;
        status_t _status;
        uint8_t _level;
        uint8_t _controlPin;
    public:
        Motor(std::string name, status_t status, uint8_t level, uint8_t controlPin)
        : _name(name), _status(status), _level(level), _controlPin(controlPin) {}

        virtual void setLevel(uint8_t level) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual uint8_t getLevel() = 0;
        virtual bool getStatus() = 0;
};