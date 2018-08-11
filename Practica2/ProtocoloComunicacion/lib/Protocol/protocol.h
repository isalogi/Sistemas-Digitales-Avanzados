#ifndef protocol_h
#define protocol_h

#include <Arduino.h>

class Protocol
{
public:
  Protocol();
  void Protocol::initBuffer(uint8_t temp);
  uint8_t calcTemp(int analogTemp);
  void clearBuffer();
  bool isHeader(uint8_t inpData);
  int analogInpRead(uint8_t inpIndex);
  uint8_t calcChecksum(uint8_t inpChecksum);
  uint8_t buffer[3];

private:
  uint8_t checkSum(uint8_t checkData);
  uint8_t origin;
  uint8_t destination;
  const uint8_t header = 0x7E;
  bool firstHeader;
};

#endif