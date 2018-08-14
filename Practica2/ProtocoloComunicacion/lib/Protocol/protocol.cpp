#include <Arduino.h>
#include "protocol.h"

Protocol::Protocol()
{
}

int Protocol::analogInpRead(uint8_t inpIndex)
{
    return analogRead(inpIndex);
}

uint8_t Protocol::calcTemp(int analogTemp)
{
    uint8_t temp = (5 * analogTemp * 100) / 1024;
    return temp;
}

void Protocol::initBuffer(uint8_t temp)
{
    this->inpBuffer[0] = this->header;
    this->inpBuffer[1] = temp;
    this->inpBuffer[2] = this->calcChecksum(temp);
}

uint8_t Protocol::calcChecksum(uint8_t inpChecksum)
{
    return this->header + inpChecksum;
}

bool Protocol::isHeader(uint8_t inpData)
{
    return inpData == this->header;
}

void Protocol::addData(uint8_t inpData)
{
    if (this->readCounter <= 3)
    {
        this->outBuffer[this->readCounter] = inpData;
        this->readCounter++;
    }
}
