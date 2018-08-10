#include "actuator.h"
#include <Servo.h>


Actuator::Actuator(short _pin)
{
    //this is for access the atributes defined in the header file of the class
    this->servoMotor.attach(_pin);
    this->pin=_pin;
}

void Actuator::turn(int _angle){
    this->servoMotor.write(_angle);
}
