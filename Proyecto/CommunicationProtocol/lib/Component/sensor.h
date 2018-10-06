#ifndef sensor_h //Evita importar dos veces la libreria
#define sensor_h

#include <Arduino.h>

//Archivo primera en minuscula y la clase en mayuscula
class Sensor
{
public:

  Sensor(uint8_t trig, uint8_t echo);
  long getValue();

private:

uint8_t trig;
uint8_t echo;

};
#endif
