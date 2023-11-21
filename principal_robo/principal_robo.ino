
#define trigPin 5 
#define echoPin 4
#define SOUND_SPEED 0.034
long duration;
float distanceCm;

#define led 2

#define motorDF 12
#define motorDT 13
#define motorET 25
#define motorEF 26


void setup() 
{
  pinMode(led,OUTPUT);
  pinMode(motorDF,OUTPUT);
  pinMode(motorDT,OUTPUT);
  pinMode(motorEF,OUTPUT);
  pinMode(motorET,OUTPUT);
  motorParado();
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("Inicialização completa");
}

void loop() 
{
  //digitalWrite(led,HIGH);// put your main code here, to run repeatedly:
  //delay(1000);
  //digitalWrite(led,LOW);
  //delay(1000);
  
  motorFrente();
 
  verificaDistancia();
  Serial.println(distanceCm);
  if(distanceCm<=20)
  {
  motorRe();
  delay(1000);
  motorHorario();
  delay(500);
  motorFrente();
  }
}
