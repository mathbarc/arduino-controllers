 /* ----- Controlador proporcional para um circuito RC ----- */
 
 
const int Referencia = 0; // O sinal de referencia sera lido a partir do pino de 
                          // entrada analogica A0

const int Sensor = 1; // O sensor sera conectado ao pino de entrada analogica A1

const int Atuador = 3; // O sinal de comando "analogico" (saida do controlador) 
                       // sera transmitido pelo pino de saida digital 5 (PWM)

int Valor_Referencia=0; // Variavel que armazenara o valor do sinal de referencia

int Valor_Sensor; // Variavel que armazenara o valor da saida (tensao no capacitor)

int Valor_Atuador; // Variavel que armazenara o valor da 
                   // saida do controlador (acao de controle)

int Erro; // Variavel que armazenara o sinal de erro (Valor_referencia - Valor_Sensor)

const float Kp = 10; // Parametro do controlador proporcional
const float T = 1800;
float anterior=0, agora;
float ct = 0;

void setup(){
  
pinMode(Sensor, INPUT); // Define o pino do sensor como uma entrada

pinMode(Referencia, INPUT); // Define o pino da referencia como uma entrada

pinMode(Atuador, OUTPUT); // Define o pino do atuador como uma saida

Serial.begin(9600); // Especifique a velocidade da comunicacao serial
pinMode(5,OUTPUT);
}



void loop(){
  agora = micros();
  if(agora-anterior>=T){
  anterior = agora;
  Valor_Referencia = analogRead(Referencia); // Converte o valor de tensao de referencia
  // numa palavra binaria de 10 bits (0V a 5V <---> 0 a 1023)
  
  Valor_Sensor = analogRead(Sensor); // Converte o valor de tensao do capacitor (saida)
  // numa palavra binaria de 10 bits (0V a 5V <---> 0 a 1023)
  
  Erro = Valor_Referencia - Valor_Sensor; // Erro pode assumir valores entre -1023 e 1023
  
  Erro = map(Erro,-512,511,-128,127); // Mapeia o intervalo [-1023, 1023] no intervalo
  // [-255, 255], visto que o saida do controlador, que e funcao so sinal de Erro, 
  //sera um sinal PWM de 8 bits
  
  Valor_Atuador = constrain(Kp*Erro,0,255); // Restringe o valor do sinal de atuacao
                                            // a faixa de 0V a 5V (0 a 255)
  
  analogWrite(Atuador, Valor_Atuador); // Escreve no pino 5 (Atuador), que simulara
                                       // uma saida analogica via PWM 
  Serial.print(Erro);
  Serial.print("\t\t");
  Serial.println(Valor_Atuador);
  ct++;
  if(ct==100){
     ct=0;
     PORTD ^= 0b00100000;
  }
  }
  
  
  //delay(100);
  
}
    
    
