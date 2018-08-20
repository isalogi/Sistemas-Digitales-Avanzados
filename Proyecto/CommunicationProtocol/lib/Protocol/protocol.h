#ifndef protocol_h //Evita importar dos veces la libreria
#define protocol_h

#include <Arduino.h>
//Archivo primera en minuscula y la clase en mayuscula
class Protocol
{
public:
  Protocol(); //Lo primero que se ejecuta cuando creo una clase
  void sendData(uint8_t inpData, uint8_t pin);
  void Read(Stream *stream, const int timeout);
  bool compareChecksum (uint8_t inpChecksum);
  uint8_t createChecksum(uint8_t* inpBuffer);
  uint8_t getData(uint8_t pin);


  uint8_t buffer[5];

private:
  const uint8_t header = 0x7e;
};
#endif
