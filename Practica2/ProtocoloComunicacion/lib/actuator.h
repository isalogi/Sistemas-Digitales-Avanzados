#include <Arduino.h>

class Actuator
{
  public:
int angle;
byte pin;

  Actuator();
  void turn();

}