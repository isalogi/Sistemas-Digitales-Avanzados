#ifndef actuator_h //Evita importar dos veces la libreria
#define actuator_h

#include <Arduino.h>
#include <Servo.h>

//Archivo primera en minuscula y la clase en mayuscula
class Actuator
{
public:
  Servo servoMotor;

  Actuator(uint8_t pin);
  void rotateServo(uint8_t *buffer);

private:
};
#endif
