#include "Arduino.h"
/*
Measuring Current Using ACS712
*/
const int analogIn = A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int motorPin = 3;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;
char[] nome;

void setup(char[] c, int motor){
 motorPin = motor;
 nome = c;
 pinMode(motorPin, OUTPUT);

}

void valoresPinagem(){
 digitalWrite(motorPin, HIGH);
 RawValue = analogRead(analogIn);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 Serial.print("Raw Value = " ); // shows pre-scaled value
 Serial.print(RawValue);
 Serial.print("\t mV = "); // shows the voltage measured
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 delay(2500);

}
