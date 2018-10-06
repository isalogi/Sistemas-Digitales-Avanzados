#include <Arduino.h>
#include "actuator.h"

Actuator::Actuator(uint8_t pin)
{
    this->pin = pin;
}

void Actuator::rotateServo(int value)
{
    uint8_t i;
    for (i = 0; i < 10; i++)
    {
        this->servoMotor.write(value);
        delay(1000);
        this->servoMotor.write(-value);
        delay(1000);
    }
}
