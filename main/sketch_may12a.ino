#include <Servo.h>

/*
  Measuring Current Using ACS712
*/
const int sensorLedGrande = A2;
const int sensorLedPequeno = A0;
const int sensorMotores = A1;
int VQ0;
int VQ1;
int VQ2;
float sensorValue = 0;
float currentValue = 0;
float voltsporUnidade = 0.0048875855327468;
float ruido = 0.00;
/*
  Servo
*/
Servo myservo;
const int servoPin = 10;
int pos = 0;
/*
  LM35
*/
int  ventrada;           // Variável para ler o sinal do pino do Arduino
float  temperatura; // Variável que recebe o valor convertido para temperatura.
const int lm35Pin = A4;
/*
  Motor
*/
const int ventuinhaPin = 3;
/*
  leds grandes
*/
const int ledG1 = 50;
const int ledG2 = 51;
const int ledG3 = 52;
const int ledG4 = 53  ;
/*
  leds pequenos
*/
const int ledP1 = 16;
const int ledP2 = 17;
const int ledP3 = 18;
const int ledP4 = 19;
/*
  botões
*/
const int bledG1 = 22;
const int bledG2 = 23;
const int bledG3 = 24;
const int bledG4 = 25;
const int bledP1 = 26;
const int bledP2 = 27;
const int bledP3 = 28;
const int bledP4 = 29;
const int bVentuinha = 30;
const int bServo = 31;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);

  pinMode(ledG1, OUTPUT);
  pinMode(ledG2, OUTPUT);
  pinMode(ledG3, OUTPUT);
  pinMode(ledG4, OUTPUT);

  pinMode(ledP1, OUTPUT);
  pinMode(ledP2, OUTPUT);
  pinMode(ledP3, OUTPUT);
  pinMode(ledP4, OUTPUT);

  pinMode(ventuinhaPin, OUTPUT);

  pinMode(bledG1, INPUT);
  pinMode(bledG2, INPUT);
  pinMode(bledG3, INPUT);
  pinMode(bledG4, INPUT);
  pinMode(bledP1, INPUT);
  pinMode(bledP2, INPUT);
  pinMode(bledP3, INPUT);
  pinMode(bledP4, INPUT);
  pinMode(bVentuinha, INPUT);
  pinMode(bServo, INPUT);

  Serial.begin(9600);


  VQ0 = determineVQ(sensorLedGrande);
  VQ1 = determineVQ(sensorLedPequeno);
  VQ2 = determineVQ(sensorMotores);
}

void loop() {
  Serial.println(retornaTemperatura());
  verificaSequenciaDeBotoes();
  verificaTemperatura();
  lerSensorVoltagemMotor();
  lerSensorVoltagemLedGrande();
  lerSensorVoltagemLedPequeno();
  delay(100);
}

void verificaSequenciaDeBotoes() {
  if (digitalRead(bledG1) == HIGH) {
    ligaLed(ledG1);
  } else {
    desligaLed(ledG1);
  }
  if (digitalRead(bledG2) == HIGH) {
    ligaLed(ledG2);
  } else {
    desligaLed(ledG2);
  }
  if (digitalRead(bledG3) == HIGH) {
    ligaLed(ledG3);
  } else {
    desligaLed(ledG3);
  }
  if (digitalRead(bledG4) == HIGH) {
    ligaLed(ledG4);
  } else {
    desligaLed(ledG4);
  }
  if (digitalRead(bledP1) == HIGH) {
    ligaLed(ledP1);
  } else {
    desligaLed(ledP1);
  }
  if (digitalRead(bledP2) == HIGH) {
    ligaLed(ledP2);
  } else {
    desligaLed(ledP2);
  }
  if (digitalRead(bledP3) == HIGH) {
    ligaLed(ledP3);
  } else {
    desligaLed(ledP3);
  }
  if (digitalRead(bledP4) == HIGH) {
    ligaLed(ledP4);
  } else {
    desligaLed(ledP4);
  }
  if (digitalRead(bVentuinha) == HIGH) {
    ligarVentuinha();
  } else {
    desligarVentuinha();
  }
  if (digitalRead(bServo) == HIGH) {
    ir();
  } else {
    voltar();
  }
}

void ligarVentuinha() {
  digitalWrite(ventuinhaPin, HIGH);
}

void desligarVentuinha() {
  digitalWrite(ventuinhaPin, LOW);
}

float retornaTemperatura() {
  ventrada = analogRead (lm35Pin);
  temperatura = (-500 * ventrada) / 1023;
  return temperatura;
}

void verificaTemperatura() {
  if (retornaTemperatura() > 25) {
    ligarVentuinha();
  }
}

void lerSensorVoltagemMotor() {
  realizarCalculoEMostrarValorSensorVoltagem(sensorMotores, VQ0);
}

void lerSensorVoltagemLedGrande() {
  realizarCalculoEMostrarValorSensorVoltagem(sensorLedGrande, VQ2);
}

void lerSensorVoltagemLedPequeno() {
  realizarCalculoEMostrarValorSensorVoltagem(sensorLedPequeno, VQ1);
}

void realizarCalculoEMostrarValorSensorVoltagem(int sensor, int VQ) {
//  currentValue = 0;
//  for (int index = 0; index < 50; index++) {
//    sensorValue = analogRead(sensor); // le o sensor na pino analogico A0
//    sensorValue = (sensorValue - 510) * voltsporUnidade; // ajusta o valor lido para volts começando da metada ja que a saída do sensor é vcc/2 para corrente =0
//    currentValue = currentValue + (sensorValue / 66) * 1000; // a saída do sensor 66 mV por amper
//  }
//
//  currentValue = currentValue / 5000;
//  // mostra o resultado no terminal
//  Serial.print("corrente = " );
//  currentValue = currentValue - ruido;
//  Serial.print(currentValue, 2);
//  Serial.print("\n" );

  int current = 0;
  int sensitivity = 100;//muda para 100 sefor ACS712-20A ou para 66 for ACS712-5A
  //le 200 vezes
  for (int i=0; i<200; i++) {
    current += abs(analogRead(sensor) - VQ);
    delay(1);
  }
  current = map(current/200, 0, 1023, 0, 5000);
  float(current)/sensitivity;

  Serial.print("Leitura: ");
  Serial.print(readCurrent(sensor, VQ),3);
  Serial.println(" mA");
}


int determineVQ(int PIN) {
  Serial.print("Estimando a Media de coeficiente de tensao:");
  long VQ = 0;
  //le 1000 amostra para estabilizar o valor
  for (int i = 0; i < 10000; i++) {
    VQ += abs(analogRead(PIN));
    delay(1);
  }
  VQ /= 10000;
  Serial.print(map(VQ, 0, 1023, 0, 5000)); Serial.println(" mV");
  return int(VQ);
}

float readCurrent(int PIN, int VQ) {
  int current = 0;
  int sensitivity = 100;//muda para 100 sefor ACS712-20A ou para 66 for ACS712-5A
  //le 200 vezes
  for (int i = 0; i < 200; i++) {
    current += abs(analogRead(PIN) - VQ);
    delay(1);
  }
  current = map(current / 200, 0, 1023, 0, 5000);
  return float(current) / sensitivity;
}

void ir() {
  myservo.write(110);              // tell servo to go to position in variable 'pos'
}

void voltar() {
  myservo.write(0);              // tell servo to go to position in variable 'pos'
}

void ligaLed(int led) {
  digitalWrite(led, HIGH);
}

void desligaLed(int led) {
  digitalWrite(led, LOW);
}
