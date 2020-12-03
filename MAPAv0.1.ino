
#include <Wtv020sd16p.h>

/*
   Feito por Pilão
   18/11/2019
   REVISA POR: PILLÃOZINHO
   19/11/2019
*/

//---------------------------------------------------------------------------------
//-------------------------------INCLUSÃO DO MÓDULO WTV----------------------------
//---------------------------------------------------------------------------------

const int resetPin = 4;  // The pin number of the reset pin.
const int clockPin = 5;  // The pin number of the clock pin.
const int dataPin = 6;  // The pin number of the data pin.
const int busyPin = 7;  // The pin number of the busy pin.

Wtv020sd16p wtv020sd16p(resetPin, clockPin, dataPin, busyPin);


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

/*
   OBS::
   COLOQUE OS
 * *PINOS
   +TEMPO DE AUDIO
 * *E O NUMERO DO AUDIO NO CARTÃO

   NA SEQUENCIA, PLMD...
*/


const int qtd_Botoes = 7; // QUANTIDADE DE BOTÕES DO MAPA
const int Botoes[qtd_Botoes] = {2, 3, 8, 9, 10, 11, 12}; // PINOS DO BOTÃO
const long Tempo_Audios[qtd_Botoes] = {22000, 19000, 36000, 16000, 28000, 15000, 15000}; //TEMPO DE CADA AUDIO
const int n_Cartao[qtd_Botoes] = {16, 6, 11, 12, 3, 14, 1}; //NÚMERO DO AUDIO DENTRO DO CARTÃO
bool Audio_Tocando[qtd_Botoes]; //VARIAVEL QUE ARMAZENA QUAL AUDIO ESTÁ TOCANDO
bool lBotoes[qtd_Botoes]; // VARIAVEL QUE ARMAZENA O ULTIMO ESTADO DO BOTÃO



unsigned long TempDesej = 0;

void setup() {
  wtv020sd16p.reset();
  Serial.begin(9600);
  Serial.println("----------------------------------");

  for (int a = 0; a < qtd_Botoes; a++) { // INICIO DOS BOTOES COLOCANDO SEU ULTIMO ESTADO IGUAL AO SEU ESTADO ATUAL
    pinMode(Botoes[a], INPUT_PULLUP);
    lBotoes[a] = digitalRead(Botoes[a]);
    Serial.print("BOTÃO DEFINIDO NO PINO: ");
    Serial.println(Botoes[a]);
    Serial.print("JUNTO DO AUDIO: ");
    Serial.println(n_Cartao[a]);
    Serial.print("COM UM TEMPO DE REPRODUÇÃO DE: ");
    Serial.println(Tempo_Audios[a]);
    Serial.println("----------------------------------");

  }
 
}

void loop() {
  for (int i = 0; i < qtd_Botoes; i++) {
    bool tbotao = digitalRead(Botoes[i]);


    Serial.println("aa");
    delay(25);

    if (Audio_Tocando[i]) { // RESENTAR AUDIO QUE RODOU
      Audio_Tocando[i] = false;
      TempDesej = 0;
      //APENAS TESTE
      Serial.print("AUDIO N°: ");
      Serial.println(n_Cartao[i]);
      Serial.println("FINALIZADO");
      Serial.println("----------------------------------");
    }
    if (tbotao != lBotoes[i]) {// SE ALGUM BOTÃO FOR PRESSIONADO
      lBotoes[i] = tbotao;
      Audio_Tocando[i] = true;
      TempDesej = Tempo_Audios[i];
      //APENAS TESTE
      Serial.print("TOCANDO AUDIO: ");
      Serial.println(n_Cartao[i]);
      Serial.print("BOTÃO APERTADO(PINO): ");
      Serial.println(Botoes[i]);
      Serial.print("TEMPO DE REPRODUÇÃO: ");
      Serial.println(Tempo_Audios[i]);
      Serial.println("TOCANDO");
      Serial.println("----------------------------------");
    }

    if (Audio_Tocando[i]) {
      Serial.println("tocandO...");
      wtv020sd16p.playVoice(n_Cartao[i]);

      delay(Tempo_Audios[i]);

      wtv020sd16p.stopVoice();
      Audio_Tocando[i] = false;
      for (int a = 0; a < qtd_Botoes; a++){
        lBotoes[a] = digitalRead(Botoes[a]);
      }
    }
  }
}// FIM VOID LOOP
