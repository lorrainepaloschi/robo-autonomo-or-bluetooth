void motorParado()
{
  digitalWrite(motorDF,LOW);
  digitalWrite(motorDT,LOW);
  digitalWrite(motorEF,LOW);
  digitalWrite(motorET,LOW);
}

void motorFrente()
{
  digitalWrite(motorDF,HIGH);
  digitalWrite(motorDT,LOW);
  digitalWrite(motorEF,HIGH);
  digitalWrite(motorET,LOW);
}

void motorRe()
{
digitalWrite(motorDT,HIGH);
digitalWrite(motorDF,LOW);
digitalWrite(motorET,HIGH);
digitalWrite(motorEF,LOW);
}
void motorHorario()
{
  digitalWrite(motorDT,HIGH);
  digitalWrite(motorDF,LOW);
  digitalWrite(motorET,LOW);
  digitalWrite(motorEF,HIGH);
}
void motorAntihorario()
{
  digitalWrite(motorDT,LOW);
  digitalWrite(motorDF,HIGH);
  digitalWrite(motorET,HIGH);
  digitalWrite(motorEF,LOW);
}
void motorDireita()
{
  digitalWrite(motorDT,LOW);
  digitalWrite(motorDF,LOW);
  digitalWrite(motorET,LOW);
  digitalWrite(motorEF,HIGH);
}
void motorEsquerda()
{
  digitalWrite(motorDF,HIGH);
  digitalWrite(motorDT,LOW);
  digitalWrite(motorET,LOW);
  digitalWrite(motorEF,LOW);
}
void motorReDireita()
{
  digitalWrite(motorDT,LOW);
  digitalWrite(motorDF,LOW);
  digitalWrite(motorET,HIGH);
  digitalWrite(motorEF,LOW);
}
void motorReEsquerda()
{
  digitalWrite(motorDF,LOW);
  digitalWrite(motorDT,HIGH);
  digitalWrite(motorET,LOW);
  digitalWrite(motorEF,LOW);
}
