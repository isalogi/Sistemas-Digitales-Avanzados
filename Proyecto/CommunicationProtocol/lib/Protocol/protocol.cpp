#include <Arduino.h>
#include "protocol.h"
#include "serialUtil.h"

Protocol::Protocol()
{
}

void Protocol::createBuffer(Stream *stream)
{
    String inpString = SerialUtil::Read(stream,2000);

    String inpHeader = "";
    String inpPin = "";
    String inpSpeed = "";

    if (inpString.length() >= 6)
    {
        inpHeader = inpString.substring(0, 3);
        inpPin = inpString.substring(4, 5);
    }

    if (inpString.length() == 8)
    {
        inpSpeed = inpString.substring(6, 7);
    }

    else if (inpString.length() == 9)
    {
        inpSpeed = inpString.substring(6, 8);
    }
    
    Serial.println(inpHeader);
    Serial.println(inpPin);
    Serial.println(inpSpeed);
}