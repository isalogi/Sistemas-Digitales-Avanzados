#include <Arduino.h>
#include <protocol.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7);

Protocol protocol;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
}

class TempSensor {
    public:
        TempSensor(uint8_t);
        void update();
        float getTemp();
    private:
        uint8_t pin;
        uint16_t buffer[10] = {0,0,0,0,0,0,0,0,0,0};
        long timer;
}; 

TempSensor::TempSensor(uint8_t _pin){
    pin = _pin;
    timer = millis();
}

void TempSensor::update(){
    if(millis()-timer > 500){
        timer = millis();
        for(int i=9; i>-1; i--){
            this->buffer[i] = this->buffer[i-1];
        }
        this->buffer[0] = analogRead(this->pin);
    }
}


float TempSensor::getTemp(){
    float value = 0;
    for(int i=0; i<10; i++){
        value += float(this->buffer[i]);
    }
    return (value/(10)) * (5.0/1023) * 1;
}

TempSensor sensor = TempSensor(A0);

void loop() {

    sensor.update();

    int analogTemp = protocol.analogInpRead(0);
    uint8_t temp = protocol.calcTemp(analogTemp);
    protocol.initBuffer(temp);
    Serial.write(protocol.inpBuffer,3);

    if (Serial.available() > 0)
    {
        uint8_t readInp = Serial.read();

        if (protocol.isHeader(readInp))
        {
            if (!protocol.firstHeader)
            {
                protocol.firstHeader = 1;
                protocol.readCounter = 0;
            }
        }
        protocol.addData(readInp);

        if (protocol.readCounter == 3)
        {
            protocol.rgb(protocol.outBuffer[1]);
            mySerial.flush();
        }
    }
}
