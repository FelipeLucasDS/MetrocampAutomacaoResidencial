#include <Servo.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//SoftwareSerial as(3, 2);
SoftwareSerial as(11, 10);
/*
  Measuring Current Using ACS712
*/
const int sensorLedGrande = A0;
const int sensorLedPequeno = A1;
const int sensorMotores = A2;
int gastoEnergiaLedGrande;
int gastoEnergiaLedPequeno;
int gastoEnergiaLedMotores;
int sensorValue_aux = 0;
float valorSensor = 0;
float valorCorrente = 0;
float voltsporUnidade = 0.004887586;
float sensibilidade = 0.066;
int tensao = 127;
/*
  Servo
*/
Servo myservo;
const int servoPin = 7;
int pos = 0;
/*
  LM35
*/
int  ventrada;           // Variável para ler o sinal do pino do Arduino
float  temperatura; // Variável que recebe o valor convertido para temperatura.
const int lm35Pin = A7;
/*
  Motor
*/
const int ventuinhaPin = 3;
/*
  leds grandes
*/
const int ledG1 = 40;
const int ledG2 = 41;
const int ledG3 = 42;
const int ledG4 = 43;
const int ledG5 = 48;
const int ledG6 = 49;
const int ledG7 = 50;
const int ledG8 = 51;
/*
  leds pequenos
*/
const int ledP1 = 44;
const int ledP2 = 45;
const int ledP3 = 46;
const int ledP4 = 47;
const int ledP5 = 52;
const int ledP6 = 53;
/*
  botões
*/
const int bledG1 = 20;
const int bledG2 = 21;
const int bledG3 = 22;
const int bledG4 = 23;
const int bledP1 = 24;
const int bledP2 = 25;
const int bledP3 = 26;
const int bledP4 = 27;
const int bVentuinha = 28;
const int bServo = 29;
/*
  variaveis
*/
int statusLedG1 = 0;
int statusLedG2 = 0;
int statusLedG3 = 0;
int statusLedG4 = 0;
int statusLedG5 = 0;
int statusLedG6 = 0;
int statusLedG7 = 0;
int statusLedG8 = 0;
int statusLedP1 = 0;
int statusLedP2 = 0;
int statusLedP3 = 0;
int statusLedP4 = 0;
int statusLedP5 = 0;
int statusLedP6 = 0;
int statusVentuinha = 0;
int statusServo = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //TODO Inserir função de paridade de serial para a serial de comunicação
  as.begin(4800);
  myservo.attach(servoPin);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledG1, OUTPUT);
  pinMode(ledG2, OUTPUT);
  pinMode(ledG3, OUTPUT);
  pinMode(ledG4, OUTPUT);
  pinMode(ledG5, OUTPUT);
  pinMode(ledG6, OUTPUT);
  pinMode(ledG7, OUTPUT);
  pinMode(ledG8, OUTPUT);

  pinMode(ledP1, OUTPUT);
  pinMode(ledP2, OUTPUT);
  pinMode(ledP3, OUTPUT);
  pinMode(ledP4, OUTPUT);
  pinMode(ledP5, OUTPUT);
  pinMode(ledP6, OUTPUT);

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
}

void loop() {
//  while (as.available() > 0) {
//    String str = as.readStringUntil('\n');
//    Serial.println(str);
//    if (str == "ler") {
//      enviaTudo();
//    } else {
//      analisaJson(str);
//    }
//  }
  verificaTemperatura();
  lerSensorVoltagemMotor();
  lerSensorVoltagemLedGrande();
  lerSensorVoltagemLedPequeno();
  if (statusServo == 0) {
      myservo.write(0);              // tell servo to go to position in variable 'pos'
  }
  delay(400);
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

}

void ligaDesligaVentuinha() {
  if (statusVentuinha == 1) {
    desligarVentuinha();
  } else {
    ligarVentuinha();
  }
}

void ligarVentuinha() {
  statusVentuinha = 1;
  digitalWrite(ventuinhaPin, HIGH);
}

void desligarVentuinha() {
  statusVentuinha = 0;
  digitalWrite(ventuinhaPin, LOW);
}

float retornaTemperatura() {
  int valorSensorAux = 0;
  for (int i = 100; i > 0; i--) {
    valorSensorAux = analogRead (lm35Pin);
    valorSensor += pow(valorSensorAux, 2);
    delay(1);
  }
  ventrada = sqrt(ventrada / 100);
  temperatura = (500 * ventrada) / 1023;
  return temperatura;
}

void verificaTemperatura() {
  int temperaturaLida = retornaTemperatura();
  Serial.println("Temperatura");
  Serial.println(temperaturaLida);
  if (retornaTemperatura() > 25) {
    ligarVentuinha();
  } else {
    desligarVentuinha();
  }
}


void lerSensorVoltagemMotor() {
  gastoEnergiaLedMotores += realizarCalculoEMostrarValorSensorVoltagem(sensorMotores) * tensao;
}

void lerSensorVoltagemLedGrande() {
  gastoEnergiaLedPequeno += realizarCalculoEMostrarValorSensorVoltagem(sensorLedGrande) * tensao;
}

void lerSensorVoltagemLedPequeno() {
  gastoEnergiaLedGrande += realizarCalculoEMostrarValorSensorVoltagem(sensorLedPequeno) * tensao;
}

int realizarCalculoEMostrarValorSensorVoltagem(int sensor) {
  for (int i = 100; i > 0; i--) {
    // le o sensor na pino analogico A0 e ajusta o valor lido ja que a saída do sensor é (1023)vcc/2 para corrente =0
    sensorValue_aux = (analogRead(sensor) - 510);
    // somam os quadrados das leituras.
    valorSensor += pow(sensorValue_aux, 2);
    delay(1);
  }

  // finaliza o calculo da média quadratica e ajusta o valor lido para volts
  valorSensor = (sqrt(valorSensor / 100)) * voltsporUnidade;
  // calcula a corrente considerando a sensibilidade do sernsor (185 mV por amper)
  valorCorrente = (valorSensor / sensibilidade);

  //tratamento para possivel ruido
  //O ACS712 para 30 Amperes é projetado para fazer leitura
  // de valores alto acima de 0.25 Amperes até 30.
  // por isso é normal ocorrer ruidos de até 0.20A
  //por isso deve ser tratado
  if (valorCorrente <= 0.095) {
    valorCorrente = 0;
  }
  valorSensor = 0;
  return valorCorrente;
}

void ir() {
  statusServo = 1;
  myservo.write(110);              // tell servo to go to position in variable 'pos'
}

void voltar() {
  statusServo = 0;
  myservo.write(0);              // tell servo to go to position in variable 'pos'

}

void irVoltarServo() {
  if (statusServo == 1) {
    voltar();
  } else {
    ir();
  }
}

void ligaLed(int led) {
  digitalWrite(led, HIGH);
}

void desligaLed(int led) {
  digitalWrite(led, LOW);
}

void enviaJsonEnergia() {
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& buffer = jsonBuffer.createObject();

  buffer["gastoEnergia1"] = gastoEnergiaLedGrande;
  buffer["gastoEnergia2"] = gastoEnergiaLedPequeno;
  buffer["gastoEnergia3"] = gastoEnergiaLedMotores;
  String str;
  buffer.printTo(str);
  Serial.print(str);
  as.print(str);
}

void enviaJsonMotores() {
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& buffer = jsonBuffer.createObject();

  buffer["ventuinha"] = statusVentuinha;
  buffer["servo"] = statusServo;
  buffer["temperatura"] = temperatura;
  String str;
  buffer.printTo(str);
  Serial.print(str);
  as.print(str);
}

void enviaJsonLeds() {
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& buffer = jsonBuffer.createObject();

  buffer["led1"] = statusLedG1;
  buffer["led2"] = statusLedG2;
  buffer["led3"] = statusLedG3;
  buffer["led4"] = statusLedG4;
  buffer["led5"] = statusLedP1;
  buffer["led6"] = statusLedP2;
  buffer["led7"] = statusLedP3;
  buffer["led8"] = statusLedP4;
  buffer["led9"] = statusLedG5;
  buffer["led10"] = statusLedG6;
  buffer["led11"] = statusLedG7;
  buffer["led12"] = statusLedG8;
  buffer["led13"] = statusLedP5;
  buffer["led14"] = statusLedP6;
  String str;
  buffer.printTo(str);
  Serial.print(str);
  as.print(str);
}


void enviaTudo() {
  enviaJsonLeds();
  enviaJsonEnergia();
  enviaJsonMotores();
  as.print('\n');
}

void analisaJson(String json) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& buffer = jsonBuffer.parseObject(json);
  if (!buffer.success()) {
    Serial.println("Json apresenta erros..");
    Serial.println(json);
    enviaTudo();
    return;
  }
  if (buffer.containsKey("ventuinha")) {
    ligaDesligaVentuinha();
  }
  if (buffer.containsKey("servo")) {
    irVoltarServo();
  }
  if (buffer.containsKey("led1")) {
    if (buffer["led1"] == "0") {
      Serial.println("desligando");
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      statusLedG1 = 0;
      desligaLed(ledG1);
    } else {
      Serial.println("ligando");
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      statusLedG1 = 1;
      ligaLed(ledG1);
    }
  }
  if (buffer.containsKey("led2")) {
    if (buffer["led2"] == "0") {
      statusLedG2 = 0;
      desligaLed(ledG2);
    } else {
      statusLedG2 = 1;
      ligaLed(ledG2);
    }
  }

  if (buffer.containsKey("led3")) {
    if (buffer["led3"] == "0") {
      statusLedG3 = 0;
      desligaLed(ledG3);
    } else {
      statusLedG3 = 1;
      ligaLed(ledG3);
    }
  }
  if (buffer.containsKey("led4")) {
    if (buffer["led4"] == "0") {
      statusLedG4 = 1;
      desligaLed(ledG4);
    } else {
      statusLedG4 = 0;
      ligaLed(ledG4);
    }
  }
  if (buffer.containsKey("led5")) {
    if (buffer["led5"] == "0") {
      statusLedP1 = 1;
      desligaLed(ledP1);
    } else {
      statusLedP1 = 0;
      ligaLed(ledP1);
    }
  }
  if (buffer.containsKey("led6")) {
    if (buffer["led6"] == "0") {
      statusLedP2 = 1;
      desligaLed(ledP2);
    } else {
      statusLedP2 = 0;
      ligaLed(ledP2);
    }
  }
  if (buffer.containsKey("led7")) {
    if (buffer["led7"] == "0") {
      statusLedP3 = 1;
      desligaLed(ledP3);
    } else {
      statusLedP3 = 0;
      ligaLed(ledP3);
    }
  }
  if (buffer.containsKey("led8")) {
    if (buffer["led8"] == "0") {
      statusLedP4 = 1;
      desligaLed(ledP4);
    } else {
      statusLedP4 = 0;
      ligaLed(ledP4);
    }
  }
  
  if (buffer.containsKey("led9")) {
    if (buffer["led9"] == "0") {
      statusLedG5 = 0;
      desligaLed(ledG5);
    } else {
      statusLedG5 = 1;
      ligaLed(ledG5);
    }
  }
  if (buffer.containsKey("led10")) {
    if (buffer["led10"] == "0") {
      statusLedG6 = 1;
      desligaLed(ledG6);
    } else {
      statusLedG6 = 0;
      ligaLed(ledG6);
    }
  }
  if (buffer.containsKey("led11")) {
    if (buffer["led11"] == "0") {
      statusLedG7 = 1;
      desligaLed(ledG7);
    } else {
      statusLedG7  = 0;
      ligaLed(ledG7);
    }
  }
  if (buffer.containsKey("led12")) {
    if (buffer["led12"] == "0") {
      statusLedG8 = 1;
      desligaLed(ledG8);
    } else {
      statusLedG8 = 0;
      ligaLed(ledG8);
    }
  }
  if (buffer.containsKey("led13")) {
    if (buffer["led13"] == "0") {
      statusLedP5 = 1;
      desligaLed(ledP5);
    } else {
      statusLedP5 = 0;
      ligaLed(ledP5);
    }
  }
  if (buffer.containsKey("led14")) {
    if (buffer["led14"] == "0") {
      statusLedP6 = 1;
      desligaLed(ledP6);
    } else {
      statusLedP6 = 0;
      ligaLed(ledP6);
    }
  }
}

