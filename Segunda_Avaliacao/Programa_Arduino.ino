//PROGRAMA: MÓDULO ESP-01 WIFI COM MQTT - PUBLICAÇÃO DE LUMINOSIDADE
//AUTOR: MATHEUS GONÇALVES STIGGER

/*
  ESTE PROGRAMA SE CONECTA A UMA REDE WIFI USANDO UM MÓDULO ESP-01.
  EM SEGUIDA, IMPRIME O VALOR DE LUMINOSIDADE E O STATUS ATUAL DO LED (ON/OFF).
*/

#include "WiFiEsp.h" //INCLUSÃO DA BIBLIOTECA
#include <PubSubClient.h> //INCLUSÃO DA BIBLIOTECA
#include "SoftwareSerial.h" //INCLUSÃO DA BIBLIOTECA

SoftwareSerial Serial1(6, 7); //PINOS QUE EMULAM A SERIAL, ONDE O PINO 6 É O TX E O PINO 7 É O RX

char ssid[] = "ssid";  //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO
char pass[] = "pass";  //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO

const char* mqttServer = "mqtt.eclipse.org";  //VARIÁVEL QUE ARMAZENA O BROKER (HOST)
const int mqttPort = 1883;  //VARIÁVEL QUE ARMAZENA A PORTA TCP

int status = WL_IDLE_STATUS;  //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
                              //ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
                              //(RESULTANDO EM WL_CONNECTED)

WiFiEspClient espClient;  //CRIA UM CLIENTE
PubSubClient client(espClient); //CRIA UMA INSTÂNCIA DO CLIENTE PARCIALMENTE INICIALIZADA. ANTES DE PODER SER USADO,
                                //OS DETALHES DO SERVIDOR DEVEM SER CONFIGURADOS

char mensagem[30];  //VARIÁVEL QUE ARMAZENA A MENSAGEM QUE SERÁ ENVIADA

int ledPin = 2; //LED NO PINO 2
int ldrPin = 0; //LDR NO PINO ANALÓGICO A0
int ldrValor = 0; //VALOR LIDO DO LDR

void setup() {

  pinMode(ledPin, OUTPUT);  //DEFINE A PORTA 2 COMO SAÍDA
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial1.begin(9600);  //INICIALIZA A SERIAL PARA O ESP8266
  WiFi.init(&Serial1);  //INICIALIZA A COMUNICAÇÃO SERIAL COM O ESP8266

  //INÍCIO - VERIFICA SE O ESP-01 ESTÁ CONECTADO AO ARDUINO E CONECTA A REDE SEM FIO

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("O Módulo WIFI não está presente!");
    while (true); //NÃO CONTINUE
  }

  //TENTA SE CONECTAR A REDE WIFI
  while ( status != WL_CONNECTED) {
    Serial.println("Iniciando conexão com a rede WIFI...");
    status = WiFi.begin(ssid, pass);  //FAZ A CONEXÃO COM A REDE
  }

  Serial.println("Conectado na rede WIFI!");

  //FIM - VERIFICA SE O ESP-01 ESTÁ CONECTADO AO ARDUINO E CONECTA A REDE SEM FIO
}

void loop() {

  //FAZ A CONEXÃO COM O BROKER MQTT
  reconectabroker();  //CHAMA A FUNÇÃO reconectabroker()

  sensorluz();  //CHAMA A FUNÇÃO sensorluz()
  
}

void sensorluz() {
  
  //FAZ A LEITURA DO VALOR DO LDR
  ldrValor = analogRead(ldrPin);  //O VALOR LIDO SERÁ ENTRE 0 E 1023

  //SE O VALOR LIDO FOR MAIOR QUE 800, LIGA O LED
  if (ldrValor >= 800) {
    
    digitalWrite(ledPin, HIGH);

    sprintf(mensagem, "LDR: %d    LED: ON", ldrValor);  //PERMITE CONSTRUIR UMA SEQUÊNCIA DE print's USANDO UM MODELO DE SEQUÊNCIA PRÉ-FORMATADO,
                                                                //NO QUAL É POSSÍVEL INSERIR VARIÁVEIS EM LOCAIS PREDEFINIDOS.

    //ENVIA A MENSAGEM AO BROKER
    client.publish("topico", mensagem);  //(TÓPICO, MENSAGEM)
    Serial.println("Mensagem enviada com sucesso!");

    //IMPRIME O VALOR LIDO DO LDR NO MONITOR SERIAL
    Serial.print("LDR: ");
    Serial.print(ldrValor);
    Serial.println("  LED: ON");

    //AGUARDA 10 SEGUNDOS PARA ENVIAR UMA NOVA MENSAGEM
    delay(10000);
    
  }
  
  //SENÃO, APAGA O LED
  else {
    
    digitalWrite(ledPin, LOW);

    sprintf(mensagem, "LDR: %d    LED: OFF", ldrValor);  //PERMITE CONSTRUIR UMA SEQUÊNCIA DE print's USANDO UM MODELO DE SEQUÊNCIA PRÉ-FORMATADO,
                                                                //NO QUAL É POSSÍVEL INSERIR VARIÁVEIS EM LOCAIS PREDEFINIDOS.

    //ENVIA A MENSAGEM AO BROKER
    client.publish("topico", mensagem);  //(TÓPICO, MENSAGEM)
    Serial.println("Mensagem enviada com sucesso!");

    //IMPRIME O VALOR LIDO DO LDR NO MONITOR SERIAL
    Serial.print("LDR: ");
    Serial.print(ldrValor);
    Serial.println("  LED: OFF");

    //AGUARDA 10 SEGUNDOS PARA ENVIAR UMA NOVA MENSAGEM
    delay(10000);
  }
  
}
  
void reconectabroker() {

  //DEFINE OS DETALHES DA CONEXÃO AO BROKER MQTT
  client.setServer(mqttServer, mqttPort); //(ENDEREÇO DO SERVIDOR, PORTA À QUAL SE CONECTAR)
   
  while (!client.connected()) {
  
    Serial.println("Conectando ao broker MQTT...");
     
    if (client.connect("Cliente_ESP-01")) { //CONECTA O CLIENTE AO BROKER
      Serial.println("Conectado ao Broker!");
    }
  
    else {
      Serial.print("Falha na conexão ao Broker!");
      delay(2000);
    }
  }
}