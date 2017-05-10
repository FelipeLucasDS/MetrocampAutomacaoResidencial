int pino;

void setup(int pin) {
  pino = pin;
  pinMode(pino, OUTPUT);
}

void ligar() {
  digitalWrite(pino, HIGH);
}

void desligar() {
  digitalWrite(pino, low);
}
