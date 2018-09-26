#include <Arduino.h>
#include<actuator.h>
#include <protocol.h> // Solo uso comillas cuando estoy importando de lib en lib
#include <Servo.h>

uint8_t pin = 6;
uint8_t trig = 8;
uint8_t echo = 12;

Protocol protocol;
Actuator actuator(pin);

void setup()
{
    actuator.servoMotor.attach(pin);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    Serial.begin(115200);
}

void loop()
{
    if (Serial.available() > 0)
    {
        //leemos los datos que nos llegan en el otro serial
        protocol.read(&Serial, 300);

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
                    actuator.rotateServo(protocol.buffer);
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
                    long duration;

                    digitalWrite(protocol.buffer[2], LOW); //para generar un pulso limpio ponemos a LOW 4us
                    delayMicroseconds(4);
                    digitalWrite(protocol.buffer[2], HIGH); //generamos Trigger (disparo) de 10us
                    delayMicroseconds(10);
                    digitalWrite(protocol.buffer[2], LOW);

                    duration = pulseIn(echo, HIGH); //medimos el tiempo entre pulsos, en microsegundos

                    uint8_t distanceCm;
                    distanceCm = duration * 10 / 292 / 2; //convertimos a distancia, en cm
                    //re-escribo la distancia en el payload

                    uint8_t *outBuffer;
                    outBuffer = protocol.getOutBuffer(distanceCm, protocol.buffer[1], protocol.buffer[2]);
                    //escribo al pc la distancia mediante el protocolo
                    Serial.write(outBuffer, 5);

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