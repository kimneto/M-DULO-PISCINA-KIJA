#include <Arduino.h>
#include <HardwareSerial.h>
#include <string.h>

const int SENSOR_ALAGAMENTO = 12;  //OK
const int SENSOR_BAROMETRICO = 4;
const int SENSOR_PRESSAO_FILTRO = 34;
const int NIVEL_ELETRODO = 34;
const int DIMMER_ELETRODO = 27;

int statusPin = 0;

// Declarando a função checkStatusSensor
void checkStatusSensor(const char* nomeSensor, int statusPino);

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_ALAGAMENTO, INPUT);
}

void loop() {
  Serial.println("#############################################");
  checkStatusSensor("SENSOR DE ALAGAMENTO:", SENSOR_ALAGAMENTO);
  checkStatusSensor("SENSOR DE BAROMETRICO:", SENSOR_BAROMETRICO);
  checkStatusSensor("SENSOR DE PRESSAO DO FILTRO:", SENSOR_PRESSAO_FILTRO);
  checkStatusSensor("SENSOR DO ELETRODO", NIVEL_ELETRODO);
  delay(1000);
}

// Definindo a função checkStatusSensor
void checkStatusSensor(const char* nomeSensor, int statusPino) {
  Serial.print(nomeSensor);
  Serial.print(" >>> ");
  Serial.println(digitalRead(statusPino));
}
