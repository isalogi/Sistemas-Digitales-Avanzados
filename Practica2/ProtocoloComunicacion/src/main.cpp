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
    analogWrite(11, 0);
    analogWrite(10, 0);
    analogWrite(9, 0);
    int analogTemp = protocol.analogInpRead(0);
    uint8_t temp = protocol.calcTemp(analogTemp);
    protocol.initBuffer(temp);                                                                                                                                                                                                                                                                                                                           
    Serial.write(protocol.inpBuffer, 3);
    delay(10000);

    Serial.println(protocol.inpBuffer[1]);

    if (Serial.available() > 0)
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
        if ((protocol.inpBuffer[1] >= 0) && (protocol.inpBuffer[1] <= 20))
        {
            analogWrite(11, 255);
            analogWrite(10, 0);
            analogWrite(9, 0);
        }
        else
        {
            analogWrite(11, 0);
            analogWrite(10, 255);
            analogWrite(9, 0);
        }
        protocol.addData(readInp);
        delay(10000);
    }
}
