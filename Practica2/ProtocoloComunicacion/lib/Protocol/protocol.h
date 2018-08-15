#ifndef protocol_h
#define protocol_h

#include <Arduino.h>

class Protocol
{
public:
  Protocol();
  bool firstHeader;
  void addData(uint8_t inpData);
  void initBuffer(uint8_t temp);
  void rgb(uint8_t temp);
  void clearBuffer();
  bool isHeader(uint8_t inpData);
  int analogInpRead(uint8_t inpIndex);
  uint8_t calcChecksum(uint8_t inpChecksum);
  uint8_t inpBuffer[3];
  uint8_t outBuffer[3];
  uint8_t calcTemp(int analogTemp);
  uint8_t readCounter;

private:
  uint8_t checkSum(uint8_t checkData);
  uint8_t origin;
  uint8_t destination;
  const uint8_t header = 0x7E;
};

#endif