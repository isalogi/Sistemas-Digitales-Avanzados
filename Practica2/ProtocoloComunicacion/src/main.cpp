#include <Arduino.h>
#include <protocol.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);

Protocol protocol;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);

    analogWrite(11, 0);
    analogWrite(10, 0);
    analogWrite(9, 0);
}

void loop()
{
    if (mySerial.available())
    {
        int analogTemp = protocol.analogInpRead(0);
        uint8_t temp = protocol.calcTemp(analogTemp);
        protocol.initBuffer(temp);
        Serial.write(protocol.inpBuffer, 3);
        delay(10000);
    }

    if (Serial.available() > 0)
    {
        uint8_t readInp = mySerial.read();

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

        if (protocol.readCounter == 3)
        {
            protocol.rgb(protocol.outBuffer[1]);
            protocol.clearBuffer;
        }
    }
}
