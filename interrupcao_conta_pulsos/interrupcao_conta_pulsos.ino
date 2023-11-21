#define pulsosDireita 5
#define pulsosEsquerda 18
#define TEMPO_DEBOUNCE 10 //ms
 
int contador0_acionamentos = 0;
int contador1_acionamentos = 0;
unsigned long timestamp0_ultimo_acionamento = 0;
unsigned long timestamp1_ultimo_acionamento = 0;
 
/* Função ISR (chamada quando há geração da
interrupção) */
void IRAM_ATTR funcao_ISR0()
{
/* Conta acionamentos do botão considerando debounce */
if ( (millis() - timestamp0_ultimo_acionamento) >= TEMPO_DEBOUNCE )
{
contador0_acionamentos++;
timestamp0_ultimo_acionamento = millis();
}

}
void IRAM_ATTR funcao_ISR1()
{
/* Conta acionamentos do botão considerando debounce */
if ( (millis() - timestamp1_ultimo_acionamento) >= TEMPO_DEBOUNCE )
{
contador1_acionamentos++;
timestamp1_ultimo_acionamento = millis();
}
} 
 
void setup()
{
Serial.begin(115200);
 
/* Configura o GPIO do botão como entrada
e configura interrupção externa no modo
RISING para ele.
*/
pinMode(pulsosDireita, INPUT);
pinMode(pulsosEsquerda, INPUT);
attachInterrupt(pulsosDireita, funcao_ISR0, RISING);
attachInterrupt(pulsosEsquerda, funcao_ISR1, RISING);
}
 
void loop()
{
Serial.print("roda direita: ");
Serial.println(contador0_acionamentos);
Serial.print("roda esquerda: ");
Serial.println(contador1_acionamentos);
delay(2000);
}
