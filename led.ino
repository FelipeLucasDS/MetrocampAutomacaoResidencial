int led;
void setup(int ledr){
  led = ledr;
  pinMode(led, OUTPUT);
}

void ligaLed(){
  analogWrite(led, HIGH);
}

void desligaLed(){
  analogWrite(led, LOW);
}
