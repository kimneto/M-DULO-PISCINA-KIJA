#include <Arduino.h>
#include <HardwareSerial.h>
#include "sensores.ino"



int statusPin = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Sensores::SENSOR_ALAGAMENTO, INPUT);
}

void loop() {
checkStatusSensor("ALAGAMENTO:", Sensores::SENSOR_ALAGAMENTO);
 
}  

void checkStatusSensor(std::string nomeSensor, int statusPino){

Serial.print(nomeSensor+" >>> ");
Serial.println(digitalRead(statusPino));
}

