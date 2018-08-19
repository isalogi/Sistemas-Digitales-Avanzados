#include <Arduino.h>
#include <protocol.h> // Solo uso comillas cuando estoy importando de lib en lib
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); //RX,TX

Protocol protocol;
void setup()
{

    Serial.begin(115200);
    mySerial.begin(115200);
}

void loop()
{
    //buffer a escribir en el primer serial
    uint8_t inpBuffer[4] = {0x7e, 02, 100, 0};

    //calculamos el checksum según los datos de buffer
    inpBuffer[3] = protocol.createChecksum(inpBuffer);

    //escribimos el buffer con los datos de entrada
    Serial.write(inpBuffer, 4);

    if (mySerial.available() > 0)
    {
        //leemos los datos que nos llegan en el otro serial
        protocol.Read(&mySerial, 1000);

        //calculamos el checksum con los datos recividos
        uint8_t inpChecksum = protocol.createChecksum(protocol.buffer);

        //comparamos el checksum que me llegó vs el que construí
        if (protocol.compareChecksum(inpChecksum))
        {
            //enviar datos al pin indicado.
        }
        else
        {
            //la cagaste
            Serial.println("Datos corruptos");
        }
    }
}