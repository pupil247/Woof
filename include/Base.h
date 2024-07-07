#include "Motor.h"

class Base : public Motor{
    public:
        virtual void setLevel(uint8_t speed){
            _level = speed;
        }
        virtual void start(){
            _status = MOTOR_ON;
            
        }

        virtual void stop(){
            _status = MOTOR_OFF;
        }

        virtual uint8_t getLevel(){
            return _level;
        }

        virtual bool getStatus(){
            return _status;
        }

        void setDirection(direction_t direction){
            _direction = direction;
        }

        direction_t getDirection(){
            return _direction;
        }
    private:
        direction_t _direction;
};