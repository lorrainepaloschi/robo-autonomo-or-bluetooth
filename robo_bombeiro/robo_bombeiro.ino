#include <Ultrasonic.h>

/* Definições dos GPIOs para leitura do sensor ultrasonico */
#define GPIO_TRIGGER_CENTER     12
#define GPIO_ECHO        11
#define GPIO_TRIGGER_ESQUERDA     10
#define GPIO_TRIGGER_DIREITA     13
 
/* Definições de operação do sensor ultrasônico */
#define DISTANCIA_MINIMA_CM                20.0 //cm
#define TEMPO_ENTRE_LEITURAS_DE_DISTANCIA  250  //ms
 
/* Definições para controle dos dois motores */
#define IN_1      9
#define IN_2      8
#define IN_3      7
#define IN_4      6


 
/* Variáveis e objetos globais */
Ultrasonic ultrasonic_center(GPIO_TRIGGER_CENTER, GPIO_ECHO);
Ultrasonic ultrasonic_direita(GPIO_TRIGGER_DIREITA, GPIO_ECHO);
Ultrasonic ultrasonic_esquerda(GPIO_TRIGGER_ESQUERDA, GPIO_ECHO);


/* Protótipos */
void configura_gpios_controle_motor(void);

float le_distancia_sensor_ultrasonico_center(void);
float le_distancia_sensor_ultrasonico_direita(void);
float le_distancia_sensor_ultrasonico_esquerda(void);
void maquina_estados_desvio_obstaculos(float distancia_obstaculo);
void re()
{
digitalWrite(IN_1,HIGH);
digitalWrite(IN_2,LOW);
digitalWrite(IN_3,HIGH);
digitalWrite(IN_4,LOW);
}
void frente()
{
digitalWrite(IN_1,LOW);
digitalWrite(IN_2,HIGH);
digitalWrite(IN_3,LOW);
digitalWrite(IN_4,HIGH);
}
void parado()
{
digitalWrite(IN_1,LOW);
digitalWrite(IN_2,LOW);
digitalWrite(IN_3,LOW);
digitalWrite(IN_4,LOW);
}
void direita()
{
digitalWrite(IN_1,LOW);
digitalWrite(IN_2,LOW);
digitalWrite(IN_3,LOW);
digitalWrite(IN_4,HIGH);
}
void esquerda()
{
digitalWrite(IN_1,LOW);
digitalWrite(IN_2,HIGH);
digitalWrite(IN_3,LOW);
digitalWrite(IN_4,LOW);
}


float le_distancia_sensor_ultrasonico_center(void)
{
    float distancia_cm = 0.0;
    long microsec = 0;
     
    microsec = ultrasonic_center.timing();
    distancia_cm = ultrasonic_center.convert(microsec, Ultrasonic::CM);
    return distancia_cm;
}
float le_distancia_sensor_ultrasonico_direita(void)
{
    float distancia_cm = 0.0;
    long microsec = 0;
     
    microsec = ultrasonic_direita.timing();
    distancia_cm = ultrasonic_direita.convert(microsec, Ultrasonic::CM);
    return distancia_cm;
}
float le_distancia_sensor_ultrasonico_esquerda(void)
{
    float distancia_cm = 0.0;
    long microsec = 0;
     
    microsec = ultrasonic_esquerda.timing();
    distancia_cm = ultrasonic_esquerda.convert(microsec, Ultrasonic::CM);
    return distancia_cm;
}
/* Função: configura GPIOs de controle do L298N como output
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void configura_gpios_controle_motor(void)
{
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
}
const int pinoLedVermelho = 3; 
const int pinoSensor = 2; 
int IN1 = 4;
int IN2 = 5;

void setup(){
  Serial.begin(9600);
  configura_gpios_controle_motor();    
  pinMode(pinoSensor, INPUT); 
  pinMode(pinoLedVermelho, OUTPUT); 
  digitalWrite(pinoLedVermelho, LOW);
  digitalWrite(pinoSensor, LOW); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}

void loop(){
  float distancia_a_frente = 0.0;
  float distancia_a_direita = 0.0;
  float distancia_a_esquerda = 0.0;
  frente();
  
  distancia_a_frente = le_distancia_sensor_ultrasonico_center();
  Serial.println("frente");
  Serial.println(distancia_a_frente);
  if(distancia_a_frente < DISTANCIA_MINIMA_CM){
    
    parado();
    distancia_a_direita = le_distancia_sensor_ultrasonico_direita();
    Serial.println("dir");
    Serial.println(distancia_a_direita);
    distancia_a_esquerda = le_distancia_sensor_ultrasonico_esquerda();
    Serial.println("esq");
    Serial.println(distancia_a_esquerda);
    if( distancia_a_esquerda > distancia_a_direita){
        parado();

    }else{
      esquerda();
    }

  }
    int fogo = 0;
  fogo = digitalRead(pinoSensor);
  if(fogo != 0){ 
      digitalWrite(pinoLedVermelho, LOW);
      digitalWrite(IN2, HIGH);               
      digitalWrite(IN1, HIGH);
  }else{ //LIGA LED VERMELHO E LIGA MOTOR COM HELICE
    digitalWrite(pinoLedVermelho, HIGH); 
    parado();
    digitalWrite(IN2, HIGH);               
    digitalWrite(IN1, LOW);
    delay(10000);
    parado();
    delay(5000);
  }


  re();
}