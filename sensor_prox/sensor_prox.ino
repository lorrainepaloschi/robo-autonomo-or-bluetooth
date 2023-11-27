#include <Ultrasonic.h>     
#define TRIGGER_PIN 12              
#define ECHO_PIN    11               
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN); 
#define IN_1      9
#define IN_2      8
#define IN_3      7
#define IN_4      6                     
                      
void setup() 
{
  pinMode(IN_1,OUTPUT);              
  pinMode(IN_2,OUTPUT);              
  pinMode(IN_3,OUTPUT);             
  pinMode(IN_4,OUTPUT);                          
  delay(1000);                    
} //end setup
void loop()                         
{
  frente();                    
  float dist_cm = distancia();     
    if(dist_cm < 20)                
    {
      decisao();
      delay(1000);
    } 
delay(100);                           
} 
float distancia()                   
{
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  return(cmMsec);                   
delay(10);
} 
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

void decisao()                      
{
  parado();
  esquerda();                    
  parado();
  re();
}