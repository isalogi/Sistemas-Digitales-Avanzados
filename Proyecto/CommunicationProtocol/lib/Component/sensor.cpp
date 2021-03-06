#include <Arduino.h>
#include "sensor.h"

Sensor::Sensor()
{
}

long Sensor::getValue()
{

    digitalWrite(this->trig, LOW); //para generar un pulso limpio ponemos a LOW 4us
    delayMicroseconds(4);
    digitalWrite(this->trig, HIGH); //generamos Trigger (disparo) de 10us
    delayMicroseconds(10);
    digitalWrite(this->trig, LOW);

    return pulseIn(this->echo, HIGH); //medimos el tiempo entre pulsos, en microsegundos
}
