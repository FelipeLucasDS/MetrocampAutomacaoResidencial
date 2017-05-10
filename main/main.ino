#include <Servo.h>

/*
  Measuring Current Using ACS712
*/
const int sensorLedGrande = A2;
const int sensorLedPequeno = A0;
const int sensorMotores = A1;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;
/*
  Servo
*/
Servo myservo; 
const int servoPin = 10;
int pos=0;
/*
  LM35
*/
int  ventrada;           // Variável para ler o sinal do pino do Arduino
float  temperatura; // Variável que recebe o valor convertido para temperatura.
const int lm35Pin = 4;
/*
  Motor
*/
const int ventuinhaPin = 3;
/*
  leds grandes
*/
const int ledG1 = 12;
const int ledG2 = 13;
const int ledG3 = 14;
const int ledG4 = 15;
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
}

void loop() {
  verificaSequenciaDeBotoes();
  verificaTemperatura();
  lerSensorVoltagemMotor();
  lerSensorVoltagemLedGrande();
  lerSensorVoltagemLedPequeno();
}

void verificaSequenciaDeBotoes(){
  if(digitalRead(bledG1) == HIGH){
    ligaLed(ledG1);
  }else{
    desligaLed(ledG1);
  }
  if(digitalRead(bledG2) == HIGH){
    ligaLed(ledG2);
  }else{
    desligaLed(ledG2);
  }
  if(digitalRead(bledG3) == HIGH){
    ligaLed(ledG3);
  }else{
    desligaLed(ledG3);
  }
  if(digitalRead(bledG4) == HIGH){
    ligaLed(ledG4);
  }else{
    desligaLed(ledG4);
  }
  if(digitalRead(bledP1) == HIGH){
    ligaLed(ledP1);
  }else{
    desligaLed(ledP1);
  }
  if(digitalRead(bledP2) == HIGH){
    ligaLed(ledP2);
  }else{
    desligaLed(ledP2);
  }
  if(digitalRead(bledP3) == HIGH){
    ligaLed(ledP3);
  }else{
    desligaLed(ledP3);
  }
  if(digitalRead(bledP4) == HIGH){
    ligaLed(ledP4);
  }else{
    desligaLed(ledP4);
  }
  if(digitalRead(bVentuinha) == HIGH){
    ligarVentuinha();
  }else{
    desligarVentuinha();
  }
  if(digitalRead(bServo) == HIGH){
     ir();
  }else{
    voltar();
  }
}

void ligarVentuinha() {
  digitalWrite(ventuinhaPin, HIGH);
}

void desligarVentuinha() {
  digitalWrite(ventuinhaPin, LOW);
}
 
float retornaTemperatura(){
  ventrada = analogRead (lm35Pin);  
  temperatura=(500*ventrada)/1023;  
  return temperatura;
}

void verificaTemperatura(){
  if(retornaTemperatura()>25){
    ligarVentuinha();
  }  
}

void lerSensorVoltagemMotor() {
  RawValue = analogRead(sensorMotores);
  realizarCalculoEMostrarValorSensorVoltagem();
}

void lerSensorVoltagemLedGrande() {
  RawValue = analogRead(sensorLedGrande);
  realizarCalculoEMostrarValorSensorVoltagem();
}

void lerSensorVoltagemLedPequeno() {
  RawValue = analogRead(sensorLedPequeno);
  realizarCalculoEMostrarValorSensorVoltagem();
}

void realizarCalculoEMostrarValorSensorVoltagem(){
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Serial.print("Raw Value = " ); // shows pre-scaled value
  Serial.print(RawValue);
  Serial.print("\t mV = "); // shows the voltage measured
  Serial.print(Voltage, 3); // the '3' after voltage allows you to display 3 digits after decimal point
  Serial.print("\t Amps = "); // shows the voltage measured
  Serial.println(Amps, 3); // the '3' after voltage allows you to display 3 digits after decimal point
}

void ir() {
  for (pos = 0; pos <= 110; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo.write(servoPin);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void voltar(){
  for (pos = 110; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(servoPin);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}

void ligaLed(int led){
  analogWrite(led, HIGH);
}

void desligaLed(int led){
  analogWrite(led, LOW);
}
