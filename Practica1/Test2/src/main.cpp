#include <Arduino.h>

int led = 22;               // led en el pin 22 
int pulsador  = 37;         // pulsador en el pin 37
int cont;

void setup() // configura los pines usados
{
  pinMode(led, OUTPUT);       // configura el led como salida
  pinMode(pulsador, INPUT);   // configura el pulsador como entrada
  digitalWrite(led, LOW);   // desactiva el led
  Serial.begin(9600);
}

void loop() // inicia el bucle del programa
{
  if(digitalRead(pulsador)==HIGH)
    {
      cont=0;
      Serial.println(cont);
      while(cont<5)
      {
        digitalWrite(led, HIGH);  // activa el led
        delay(500);               // espera medio segundo
        digitalWrite(led, LOW);   // desactiva el led
        delay(500);               // espera 1 segundo
        cont++;
        Serial.println(cont);
      }
    }  
}