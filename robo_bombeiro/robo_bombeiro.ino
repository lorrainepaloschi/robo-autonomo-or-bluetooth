#include <Ultrasonic.h>

/* Definições dos GPIOs para leitura do sensor ultrasonico */
#define GPIO_TRIGGER_CENTRO 12
#define GPIO_ECHO 11
#define GPIO_TRIGGER_DIREITA 10
#define GPIO_TRIGGER_ESQUERDA 13


/* Definições para controle dos dois motores */
#define IN_1 9
#define IN_2 8
#define IN_3 7
#define IN_4 6


void frente() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
}
void re() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
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
  digitalWrite(IN_1,HIGH);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);
}
void parado()
{
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);
}

void configura_gpios_controle_motor(void) {
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
}
/* Função: controle um motor (freia, movimento anti-horário, movimento horário
 *         ou ponto morto)
 * Parâmetros: motor a ser controlado e ação desejada
 * Retorno: nenhum
 */




const int pinoLedVermelho = 3;
const int pinoSensor = 2;
int IN1 = 4;
int IN2 = 5;

void setup() {
  configura_gpios_controle_motor();

  pinMode(pinoSensor, INPUT);
  pinMode(pinoLedVermelho, OUTPUT);
  digitalWrite(pinoLedVermelho, LOW);
  digitalWrite(pinoSensor, LOW);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(GPIO_TRIGGER_CENTRO, OUTPUT);
  digitalWrite(GPIO_ECHO, INPUT);
  digitalWrite(GPIO_TRIGGER_DIREITA, OUTPUT);
  digitalWrite(GPIO_TRIGGER_ESQUERDA, OUTPUT);

}
//Get the sensor values
int sensorOne() {
  //pulse output
  digitalWrite(GPIO_TRIGGER_ESQUERDA, LOW);
  delayMicroseconds(4);
  digitalWrite(GPIO_TRIGGER_ESQUERDA, HIGH);
  delayMicroseconds(10);
  digitalWrite(GPIO_TRIGGER_ESQUERDA, LOW);

  long t = pulseIn(GPIO_ECHO, HIGH);//Get the pulse
  int cm = t / 29 / 2; //Convert time to the distance
  return cm; // Return the values from the sensor
}

//Get the sensor values
int sensorTwo() {
  //pulse output
  digitalWrite(GPIO_TRIGGER_CENTRO, LOW);
  delayMicroseconds(4);
  digitalWrite(GPIO_TRIGGER_CENTRO, HIGH);
  delayMicroseconds(10);
  digitalWrite(GPIO_TRIGGER_CENTRO, LOW);

  long t = pulseIn(GPIO_ECHO, HIGH);//Get the pulse
  int cm = t / 29 / 2; //Convert time to the distance
  return cm; // Return the values from the sensor
}

//Get the sensor values
int sensorThree() {
  //pulse output
  digitalWrite(GPIO_TRIGGER_DIREITA, LOW);
  delayMicroseconds(4);
  digitalWrite(GPIO_TRIGGER_DIREITA, HIGH);
  delayMicroseconds(10);
  digitalWrite(GPIO_TRIGGER_DIREITA, LOW);

  long t = pulseIn(GPIO_ECHO, HIGH);//Get the pulse
  int cm = t / 29 / 2; //Convert time to the distance
  return cm; // Return the values from the sensor
}

void loop() {
  int centerSensor = sensorTwo();
  int leftSensor = sensorOne();
  int rightSensor = sensorThree();

  if (15 >= centerSensor){
    parado();
    delay(1000);
    if(leftSensor > rightSensor ){
      esquerda();
      delay(500);
    } else{
      direita();
      delay(500);
    }
  }

  int fogo = 0;
  fogo = digitalRead(pinoSensor);
  if (fogo != 0) {
    digitalWrite(pinoLedVermelho, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, HIGH);

  frente();


  } else {  //LIGA LED VERMELHO E LIGA MOTOR COM HELICE
    digitalWrite(pinoLedVermelho, HIGH);

    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);

    delay(5000);
  }
  
}