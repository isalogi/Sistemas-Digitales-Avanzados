#include <Arduino.h>
#include <protocol.h>

Protocol protocol;

void setup()
{
    Serial.begin(115200);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
}

void loop()
{

    int analogTemp = protocol.analogInpRead(0);
    uint8_t temp = protocol.calcTemp(analogTemp);
    protocol.initBuffer(temp);

    Serial.print("Input: ");
    Serial.println(protocol.inpBuffer[1]);

    Serial.write(protocol.inpBuffer, 3);
    delay(10000);

    if (Serial.available())
    {
        uint8_t readInp = Serial.read();

        if (protocol.isHeader(readInp))
        {
            if (!protocol.firstHeader)
            {
                protocol.firstHeader = 1;
                protocol.readCounter = 0;
            }
        }
        protocol.addData(readInp);

        delay(10000);
    }
}
