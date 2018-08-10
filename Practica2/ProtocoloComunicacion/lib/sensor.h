#ifndef sensor_h
#define sensor_h

#include <Arduino.h>

class Sensor
{
  public:
    Sensor(short _pin);
    double getTemp();

  private:
    int temp;
    short pin;
};

#endif