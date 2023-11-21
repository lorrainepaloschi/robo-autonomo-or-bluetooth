#include <Ultrasonic.h>

/* Definições dos GPIOs para leitura do sensor ultrasonico */
#define GPIO_TRIGGER     12
#define GPIO_ECHO        11
 
/* Definições de operação do sensor ultrasônico */
#define DISTANCIA_MINIMA_CM                20.0 //cm
#define TEMPO_ENTRE_LEITURAS_DE_DISTANCIA  250  //ms
 
/* Definições para controle dos dois motores */
#define IN_1      9
#define IN_2      8
#define IN_3      7
#define IN_4      6


/* Definições dos motores a serem controlados */
#define MOTOR_A                      0x00
#define MOTOR_B                      0x01
 
/* Definições das ações dos motores */
#define ACAO_FREIO                   0x00
#define ACAO_MOVIMENTO_ANTI_HORARIO  0x01
#define ACAO_MOVIMENTO_HORARIO       0x02
#define ACAO_PONTO_MORTO             0x03
 
/* Definições de sentido de giro (em caso de obstáculo) */
#define SENTIDO_GIRO_ANTI_HORARIO    0x00
#define SENTIDO_GIRO_HORARIO         0x01
 
/* Definições do desvio de objetos */
#define ESTADO_AGUARDA_OBSTACULO     0x00
#define ESTADO_GIRANDO               0x01
 
/* Variáveis e objetos globais */
Ultrasonic ultrasonic(GPIO_TRIGGER, GPIO_ECHO);
char ultimo_lado_que_girou = SENTIDO_GIRO_ANTI_HORARIO;
char estado_desvio_obstaculos = ESTADO_AGUARDA_OBSTACULO;
 
/* Protótipos */
void configura_gpios_controle_motor(void);
void controla_motor(char motor, char acao);
float le_distancia_sensor_ultrasonico(void);
void maquina_estados_desvio_obstaculos(float distancia_obstaculo);
void motorRe()
{
digitalWrite(IN_1,HIGH);
digitalWrite(IN_2,LOW);
digitalWrite(IN_3,HIGH);
digitalWrite(IN_4,LOW);
}

float le_distancia_sensor_ultrasonico(void)
{
    float distancia_cm = 0.0;
    long microsec = 0;
     
    microsec = ultrasonic.timing();
    distancia_cm = ultrasonic.convert(microsec, Ultrasonic::CM);
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
/* Função: controle um motor (freia, movimento anti-horário, movimento horário
 *         ou ponto morto)
 * Parâmetros: motor a ser controlado e ação desejada
 * Retorno: nenhum
 */
void controla_motor(char motor, char acao)
{
    int gpio_1_motor = 0;
    int gpio_2_motor = 0;
 
    /* seleciona os GPIOs de acordo com o motor desejado */
    switch(motor)
    {
        case MOTOR_A:
            gpio_1_motor = IN_2;
            gpio_2_motor = IN_1;
            break;
     
        case MOTOR_B:
            gpio_1_motor = IN_4;
            gpio_2_motor = IN_3;
            break;
 
        default:
            /* Motor inválido. Nada mais deve ser feito nesta função */
            return;            
    }
 
    /* Controla o motor conforme ação desejada */
    switch(acao)
    {
        case ACAO_FREIO:
            digitalWrite(gpio_1_motor, HIGH);
            digitalWrite(gpio_2_motor, HIGH);
            break;
 
        case ACAO_MOVIMENTO_ANTI_HORARIO:
            digitalWrite(gpio_1_motor, LOW);
            digitalWrite(gpio_2_motor, HIGH);
            break;
 
        case ACAO_MOVIMENTO_HORARIO:
            digitalWrite(gpio_1_motor, HIGH);
            digitalWrite(gpio_2_motor, LOW);
            break;
 
        case ACAO_PONTO_MORTO:
            digitalWrite(gpio_1_motor, LOW);
            digitalWrite(gpio_2_motor, LOW);
            break;
 
        default:
            /* Ação inválida. Nada mais deve ser feito nesta função */
            return;                                                            
    }    
}
 
/* Função: maquina de estado responsavel por controlar o desvio de obstáculos
 * Parâmetros: distância de obstáculo a frente
 * Retorno: nenhum
 */
void maquina_estados_desvio_obstaculos(float distancia_obstaculo)
{
    switch(estado_desvio_obstaculos)
    {
        case ESTADO_AGUARDA_OBSTACULO:
            if (distancia_obstaculo <= DISTANCIA_MINIMA_CM)
            {
                /* Obstáculo encontrado. O robô deve girar para
                   desviar dele */
                Serial.println("[MOVIMENTO] Obstaculo encontrado!"); 
                controla_motor(MOTOR_A, ACAO_PONTO_MORTO);
                controla_motor(MOTOR_B, ACAO_PONTO_MORTO);
                delay(500);
                motorRe();
                delay(1000);

                 
                /* Alterna sentido de giro para se livrar de obstáculos
                   (para otimizar o desvio de obstáculos) */
                if (ultimo_lado_que_girou == SENTIDO_GIRO_ANTI_HORARIO){
                    ultimo_lado_que_girou = SENTIDO_GIRO_HORARIO;
                    controla_motor(MOTOR_A, ACAO_PONTO_MORTO);
                    controla_motor(MOTOR_B, ACAO_PONTO_MORTO);
                    delay(500);
                }
                else{
                    ultimo_lado_que_girou = SENTIDO_GIRO_ANTI_HORARIO;
                    controla_motor(MOTOR_A, ACAO_PONTO_MORTO);
                    controla_motor(MOTOR_B, ACAO_PONTO_MORTO);
                    delay(500);
                }     
                estado_desvio_obstaculos = ESTADO_GIRANDO; 
            }
            else
            {
                Serial.println("[MOVIMENTO] Sem obstaculos a frente");
                 
                /* Se não há obstáculos, continua em frente */
                controla_motor(MOTOR_A, ACAO_MOVIMENTO_HORARIO);
                controla_motor(MOTOR_B, ACAO_MOVIMENTO_HORARIO);
            }
             
            break;
 
        case ESTADO_GIRANDO: 
            if (distancia_obstaculo > DISTANCIA_MINIMA_CM)
            {
                /* Não há mais obstáculo a frente do robô */  
                estado_desvio_obstaculos = ESTADO_AGUARDA_OBSTACULO; 
            }
            else
            {
                if (ultimo_lado_que_girou == SENTIDO_GIRO_ANTI_HORARIO)
                {
                    controla_motor(MOTOR_A, ACAO_MOVIMENTO_ANTI_HORARIO);
                    controla_motor(MOTOR_B, ACAO_MOVIMENTO_HORARIO);
                    Serial.println("[MOVIMENTO] Girando no sentido anti-horario...");
                }
                else
                {
                    controla_motor(MOTOR_A, ACAO_MOVIMENTO_HORARIO);
                    controla_motor(MOTOR_B, ACAO_MOVIMENTO_ANTI_HORARIO);
                    Serial.println("[MOVIMENTO] Girando no sentido horario...");
                }
            }
             
            break;
    }
}


const int pinoLedVermelho = 3; 
const int pinoSensor = 2; 
int IN1 = 4;
int IN2 = 5;

void setup(){
  configura_gpios_controle_motor();    
  controla_motor(MOTOR_A, ACAO_FREIO);
  controla_motor(MOTOR_B, ACAO_FREIO);
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
  distancia_a_frente = le_distancia_sensor_ultrasonico();

  maquina_estados_desvio_obstaculos(distancia_a_frente);
  int fogo = 0;
  fogo = digitalRead(pinoSensor);
  if(fogo != 0 ){ 
      digitalWrite(pinoLedVermelho, LOW);
      digitalWrite(IN2, HIGH);               
      digitalWrite(IN1, HIGH);
      
      
  }else{ //LIGA LED VERMELHO E LIGA MOTOR COM HELICE
    digitalWrite(pinoLedVermelho, HIGH); 
    digitalWrite(IN2, HIGH);               
    digitalWrite(IN1, LOW);
    controla_motor(MOTOR_A, ACAO_FREIO);
    controla_motor(MOTOR_B, ACAO_FREIO);  
    
  }
  delay(TEMPO_ENTRE_LEITURAS_DE_DISTANCIA);
}
