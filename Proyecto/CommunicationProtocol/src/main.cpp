#include <Arduino.h>
#include <protocol.h> // Solo uso comillas cuando estoy importando de lib en lib

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
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(pin, 0);

    Serial.begin(115200);
}

void loop()
{
    //leemos los datos que nos llegan en el otro serial
    protocol.Read(&Serial, 1000);

    //calculamos el checksum con los datos recividos
    uint8_t inpChecksum = protocol.createChecksum(protocol.buffer);

    //comparamos el checksum que me llegó vs el que construí
    if (protocol.compareChecksum(inpChecksum))
    {
        if (protocol.buffer[1] == 1) //actuador o sensor
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
            case 8:
                long duration, distanceCm;

                digitalWrite(protocol.buffer[2], LOW); //para generar un pulso limpio ponemos a LOW 4us
                delayMicroseconds(4);
                digitalWrite(protocol.buffer[2], HIGH); //generamos Trigger (disparo) de 10us
                delayMicroseconds(10);
                digitalWrite(protocol.buffer[2], LOW);

                duration = pulseIn(echo, HIGH); //medimos el tiempo entre pulsos, en microsegundos

                distanceCm = duration * 10 / 292 / 2; //convertimos a distancia, en cm

                Serial.write("Distancia: ");
                Serial.write(distanceCm);
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