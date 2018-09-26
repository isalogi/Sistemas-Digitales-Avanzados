#include <Arduino.h>
#include "actuator.h"

Actuator::Actuator(uint8_t pin)
{
}

void Actuator::rotateServo(uint8_t *buffer)
{
    uint8_t i;
    for (i = 0; i < 10; i++)
    {
        this->servoMotor.write(static_cast<int>(buffer[3]));
        delay(1000);
        this->servoMotor.write(static_cast<int>(-buffer[3]));
        delay(1000);
    }
}
