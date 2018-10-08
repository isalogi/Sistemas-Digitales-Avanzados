#include <Arduino.h>
#include <actuator.h>
#include <protocol.h> // Solo uso comillas cuando estoy importando de lib en lib
#include <Servo.h>
#include <sensor.h>

uint8_t echo = 12;

Protocol protocol;
Actuator actuator;
Sensor sensor;

void setup()
{
    pinMode(echo, INPUT);

    Serial.begin(115200);
}

void loop()
{
    if (Serial.available() > 0)
    {
        uint8_t response;
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

                    response = 0x01; //ok motor se movio
                    actuator.pin = protocol.buffer[2];
                    actuator.servoMotor.attach(actuator.pin);
                    actuator.rotateServo(static_cast<int>(protocol.buffer[3]));

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
                    sensor.echo = echo;
                    sensor.trig = protocol.buffer[2];

                    pinMode(sensor.trig, OUTPUT);

                    long duration;
                    // Promedio de medidas del sensor de distancia
                    int add;
                    add=0;
                    for (size_t i = 0; i < 4; i++)
                    {
                        duration = sensor.getValue();
                        response= duration * 10 / 292 / 2;
                        add+=response;
                    }
                    response = add/ 3;

                    //distanceCm = duration * 10 / 292 / 2; //convertimos a distancia, en cm
                    //re-escribo la distancia en el payload
                default:
                    break;
                }
            }

            uint8_t *outBuffer;
            outBuffer = protocol.getOutBuffer(response, protocol.buffer[1], protocol.buffer[2]);
            //escribo que ya realizo la tarea.
            Serial.write(outBuffer, 5);
        }
        else
        {
            Serial.println("Datos corruptos");
        }
    }
}