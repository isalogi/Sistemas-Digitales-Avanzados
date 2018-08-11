#include <Arduino.h>
#include <protocol.h>

Protocol protocol;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available())
    {
        int analogTemp = protocol.analogInpRead(0);
        uint8_t temp = protocol.calcTemp(analogTemp);
        protocol.initBuffer(temp);

        Serial.write(protocol.buffer, 3);
        delay(100);
    }
}
