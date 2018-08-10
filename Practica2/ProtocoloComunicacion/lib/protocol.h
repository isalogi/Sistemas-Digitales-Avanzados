#ifndef protocol_h
#define protocol_h

#include <Arduino.h>

class Protocol
{
  public:
  Protocol();
  void initBuffer(uint8_t origin, uint8_t destination, uint8_t temp);
  int calcTemp (int analogTemp );
  void clearBuffer();
  bool isHeader(uint8_t inpData);

  private:
  uint8_t buffer[3];
  uint8_t checkSum(uint8_t checkData);
  uint8_t origin;
  uint8_t destination;
  uint8_t temp;
  const uint8_t header = 0x7E;
  bool firstHeader;

};

#endif