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
    this->buffer[0]=this->header;
    this->buffer[1]=temp;
    this->buffer[2]=this->calcChecksum(temp);
}

  uint8_t Protocol::calcChecksum (uint8_t inpChecksum)
  {
      return this->header + inpChecksum;
  }
