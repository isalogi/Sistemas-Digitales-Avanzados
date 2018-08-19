#include <Arduino.h>
#include <protocol.h> // Solo uso comillas cuando estoy importando de lib en lib

Protocol protocol;
void setup()
{

    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        protocol.createBuffer(&Serial); //Serial es una variable y se necesita enviar la direccion de la variable
    }
}