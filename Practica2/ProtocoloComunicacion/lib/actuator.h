#ifndef actuator_h
#define actuator_h

#include <Servo.h>
#include <Arduino.h>

class Actuator
{
public:
  Actuator(short _pin);
  void turn(int _angle);

private:
  short pin;
  Servo servoMotor;
};

#endif