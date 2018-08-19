#ifndef protocol_h //Evita importar dos veces la libreria
#define protocol_h

#include <Arduino.h>
//Archivo primera en minuscula y la clase en mayuscula
class Protocol
{
  public:
    Protocol(); //Lo primero que se ejecuta cuando creo una clase
    void sendData(uint8_t inpData, uint8_t pin);
    uint8_t getData(uint8_t pin);
    void createBuffer(Stream *stream);

    uint8_t buffer[4];

  private:
    const uint8_t header = 0x7e;
};
#endif
