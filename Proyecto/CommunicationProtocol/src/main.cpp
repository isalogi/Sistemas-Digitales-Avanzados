#include <Arduino.h>
#include <protocol.h> // Solo uso comillas cuando estoy importando de lib en lib
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //RX,TX
uint8_t d1 = 4;
uint8_t d2 = 5;
uint8_t pin = 6;
uint8_t trig = 8;
uint8_t echo = 12;

Protocol protocol;
void setup()
{
    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(pin, OUTPUT);

    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(pin, 0);

    Serial.begin(115200);
    mySerial.begin(115200);
}

void loop()
{
    //buffer a escribir en el primer serial
    uint8_t inpBufferActuador[5] = {0x7e, 1, pin, 80, 0};
    //procesar sensor
    uint8_t inpBufferSensor[5] = {0x7e, 0, pin, 0, 0};

    //calculamos el checksum según los datos de buffer
    inpBufferActuador[4] = protocol.createChecksum(inpBufferActuador);

    //escribimos el buffer con los datos de entrada
    mySerial.write(inpBufferActuador, 5);

    if (Serial.available() > 0)
    {
        //leemos los datos que nos llegan en el otro serial
        protocol.Read(&Serial, 1000);

        //calculamos el checksum con los datos recividos
        uint8_t inpChecksum = protocol.createChecksum(protocol.buffer);

        //comparamos el checksum que me llegó vs el que construí
        if (protocol.compareChecksum(inpChecksum))
        {
            if (protocol.buffer[1] == 0) //actuador o sensor
            {

                switch (protocol.buffer[2])
                {
                case 6:
                    digitalWrite(d1, HIGH);
                    digitalWrite(d2, LOW);
                    digitalWrite(protocol.buffer[2], protocol.buffer[3]);
                    break;

                default:

                    break;
                }
            }
            else
            {
                switch (protocol.buffer[2])
                {
                case 6:
                    digitalWrite(d1, HIGH);
                    digitalWrite(d2, LOW);
                    digitalWrite(protocol.buffer[2], protocol.buffer[3]);
                    break;

                default:

                    break;
                }
            }
        }
        else
        {
            Serial.println("Datos corruptos");
        }
    }
}