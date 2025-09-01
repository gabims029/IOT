#include <math.h>
#include "AdafruitIO_WiFi.h"

//configurações da rede Wifi
#define WIFI_SSID "..."
#define WIFI_PASS "..."

//Autenticação Adafruit IO
#define IO_USERNAME "..."
#define IO_KEY "..."

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinNTC 34
#define pinLed 14 // Pino do LED

//Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

//Variável / ponteiro para referenciar o feed temperatura
AdafruitIO_Feed *botaoled = io.feed("botaoled");

const float Rfixo = 10000.0; //Resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000; // Nominal do ntc
const float T0_kelvin = 298.15; // 25°C em Kelvin
const float Vcc = 3.3;

void setup() {
  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);

  Serial.begin(115200);

  while(!Serial);

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  // Configuração do callback, quando o feed receber(atualizar) um valor
  botaoled -> onMessage(handleBotaoLed);
  // Registra a função de callback 
  // Ela será chamada sempre que o feed receber um novo dado

  delay(1000);
}

void loop() {

  //Manter a conexão com o Adafruit IO ativa
  io.run();
  
  //publicacao(); // Chamada da função publish

  delay(500);
}
