// Pinagem de Entrada
const int pinoSensorBarometrico = 2;      // Pino do sensor barométrico
const int pinoSensorPressaoFiltro = 5;    // Pino do sensor de pressão do filtro
const int pinoSensorAlagamento = 4;        // Pino do sensor de alagamento
const int pinoSensorTrocaEletrodo = 18;   // Pino do sensor de troca de eletrodo
const int pinoDimmer = 34;                 // Pino do dimmer

// Pinagem de Saída
const int pinoEletrodo = 17;               // Pino de controle do eletrodo (conectado ao eletrodo de ionização)
const int pinoLEDGeral = 13;               // Pino do LED geral (conectado ao LED e ao resistor de 220 ohms)
const int pinoLEDSensorBarometrico = 14;  // Pino do LED do sensor barométrico
const int pinoLEDSensorPressaoFiltro = 15; // Pino do LED do sensor de pressão do filtro
const int pinoLEDSensorAlagamento = 16;    // Pino do LED do sensor de alagamento
const int pinoLEDSensorTrocaEletrodo = 19; // Pino do LED do sensor de troca de eletrodo
         // Pino
int valorPWM = 0;                      // Variável para armazenar o valor PWM

void setup() {
  pinMode(pinoEletrodo, OUTPUT);
  pinMode(pinoSensorBarometrico, INPUT);
  pinMode(pinoSensorPressaoFiltro, INPUT);
  pinMode(pinoSensorAlagamento, INPUT);
  pinMode(pinoSensorTrocaEletrodo, INPUT);
  
  pinMode(pinoLEDGeral, OUTPUT);
  pinMode(pinoLEDSensorBarometrico, OUTPUT);
  pinMode(pinoLEDSensorPressaoFiltro, OUTPUT);
  pinMode(pinoLEDSensorAlagamento, OUTPUT);
  pinMode(pinoLEDSensorTrocaEletrodo, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int valorDimmer = analogRead(pinoDimmer) / 4; // Leitura do valor do dimmer (0-4095) convertido para (0-254)

  Serial.print("Digite o valor PWM (0-254) para o eletrodo de ionização: ");
  
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available() > 0) {
    valorPWM = Serial.parseInt(); // Lê o valor digitado como um número inteiro
    Serial.println(valorPWM);

    // Limita o valor de valorPWM entre 0 e 254
    valorPWM = constrain(valorPWM, 0, 254);
  }

  // Controle do eletrodo de ionização
  ledcSetup(0, 5000, 8); // Configuração do canal PWM
  ledcAttachPin(pinoEletrodo, 0); // Conecta o pino ao canal PWM
  ledcWrite(0, max(valorPWM, valorDimmer));

  // Verificar os sensores binários
  verificarSensorBinario(pinoSensorBarometrico, pinoLEDSensorBarometrico);
  verificarSensorBinario(pinoSensorPressaoFiltro, pinoLEDSensorPressaoFiltro);
  verificarSensorBinario(pinoSensorAlagamento, pinoLEDSensorAlagamento);
  verificarSensorBinario(pinoSensorTrocaEletrodo, pinoLEDSensorTrocaEletrodo);
  
  // Pisca o LED geral com uma frequência proporcional ao valor PWM
  int frequenciaPiscarLED = map(valorPWM, 0, 254, 1000, 100); // Mapeia o valor PWM para a frequência do LED
  digitalWrite(pinoLEDGeral, HIGH);
  delay(frequenciaPiscarLED / 2);
  digitalWrite(pinoLEDGeral, LOW);
  delay(frequenciaPiscarLED / 2);
}

void verificarSensorBinario(int pinoSensor, int pinoLED) {
  int estadoSensor = digitalRead(pinoSensor);
  
  if (estadoSensor == HIGH) {
      piscarLED(pinoLED, 100);
  } else {
      digitalWrite(pinoLED, LOW);
  }
}

void piscarLED(int pinoLED, int tempoAtraso) {
  digitalWrite(pinoLED, HIGH);
  delay(tempoAtraso);
  digitalWrite(pinoLED, LOW);
  delay(tempoAtraso);
}
