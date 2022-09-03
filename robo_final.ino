#include <Servo.h>  
           
#define ENA  11       
#define IN1  9         
#define IN2  8            
#define ENB  5         
#define IN3  7         
#define IN4  6         
#define TRIGGER 2
#define ECHO 3

Servo servoSensor;  
int distanciaParaDireita, distanciaParaEsquerda;  
int Distancia = 0;  
int velocidadeMotorUm = 100;
int velocidadeMotorDois = 120;


void setup() {
  Serial.begin(9600);   
  servoSensor.attach(13);  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIGGER,OUTPUT);
  pinMode(ECHO,INPUT);  
}

void loop() {
  servoSensor.write(90);                           
  delay(100);                                      
  Distancia = medeDistancia();                         
  Serial.print("Distancia dentro do loop: " );
  Serial.println(Distancia);
  if (Distancia < 40) {                             
    direcao();                                      
  }
  else if (Distancia >= 40)  {                      
    andarParaFrente();                                      
  }
  
}

void direcao() {        
  pararDeAndar();                                         
  andarParaTras();                                     
  pararDeAndar();                                      
  servoSensor.write(180);                          
  delay(1000);              
  distanciaParaEsquerda = medeDistancia();                 
  delay(500);               
  servoSensor.write(0);                            
  delay(500);               
  distanciaParaDireita = medeDistancia();                 
  delay(500);               
  servoSensor.write(90);                          
  delay(500);              
  CompareDistance();                               
}


void CompareDistance() { 
  if (distanciaParaDireita > distanciaParaEsquerda) {       
    virarParaDireita();                                
  }
  else if (distanciaParaEsquerda > distanciaParaDireita) {  
    virarParaEsquerda();                              
  }
  else {                                           
    retornar();                                    
  }
}

void pararDeAndar()
{
  Serial.println("Parar de Andar ");
  digitalWrite(IN1, LOW);                            
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);                                       
}

void andarParaFrente()
{
  Serial.println("Andar para Frente ");
  digitalWrite(IN1, HIGH);                           
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  configuraVelocidadeMotores();
}

void andarParaTras()
{
  Serial.println("Andar para Trás ");
  digitalWrite(IN1, LOW);                           
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);                                       
  configuraVelocidadeMotores();
}

void virarParaDireita()
{
  Serial.println("Virar para Direita");
  digitalWrite(IN1, LOW);                           
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(300);                                       
  configuraVelocidadeMotores();                        
}

void virarParaEsquerda()
{
  Serial.println("Virar para Esquerda");                
  digitalWrite(IN1, HIGH);                             
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);                                      
  configuraVelocidadeMotores();
}

void retornar() {    
  Serial.println("Retornar");      
  digitalWrite(IN1, HIGH);                          
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(700);                                      
  configuraVelocidadeMotores();
}

void configuraVelocidadeMotores(){
    analogWrite(ENA, velocidadeMotorUm);              
    analogWrite(ENB, velocidadeMotorDois);              
}

int medeDistancia() {
  int cm = 0; 
  digitalWrite(TRIGGER,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER,LOW); 
  cm =  pulseIn(ECHO,HIGH)/59;
  Serial.println(cm);    
  return cm;
}
