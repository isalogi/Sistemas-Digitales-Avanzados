#include <Arduino.h>
#include "protocol.h"

Protocol::Protocol()
{
}

void Protocol::Read(Stream *stream, const int timeout)
{
    uint8_t tempData[3];

    unsigned long int time = millis() + timeout;
    while (time > millis())
    {
        while (stream->available())
        {
            uint8_t c = stream->read();
            if (c == this->header)
            {
                stream->readBytes(tempData, 3);
                this->buffer[0] = c;
                this->buffer[1] = tempData[0];
                this->buffer[2] = tempData[1];
                this->buffer[3] = tempData[2];
            }
        }
    }
}

uint8_t Protocol::createChecksum(uint8_t* inpBuffer)
{
    return inpBuffer[0] + inpBuffer[1] + inpBuffer[2];
}

bool Protocol::compareChecksum(uint8_t inpChecksum)
{
    return this->buffer[3] == inpChecksum;
}
