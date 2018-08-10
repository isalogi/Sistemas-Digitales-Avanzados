#include <Arduino.h>

class Sensor
{
public:
  int temp;
  short pin;

  Sensor(short _pin);
  double getTemp();
}