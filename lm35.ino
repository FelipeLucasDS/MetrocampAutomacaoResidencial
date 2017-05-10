 
int  ventrada;           // Variável para ler o sinal do pino do Arduino
float  temperatura; // Variável que recebe o valor convertido para temperatura.
int sensor;
 
void  setup(int pino){
  sensor = pino;
}
 
float retornaTemperatura(){
  ventrada = analogRead (sensor);  
  temperatura=(500*ventrada)/1023;  
  return temperatura;
}
