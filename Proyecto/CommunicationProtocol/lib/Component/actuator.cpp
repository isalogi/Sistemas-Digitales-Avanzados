#include <Arduino.h>
#include "actuator.h"

Actuator::Actuator()
{
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
