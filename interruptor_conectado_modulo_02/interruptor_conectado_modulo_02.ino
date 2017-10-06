

/*
 * Minha Casa Conectada
 * http://minhacasaconectada.blogspot.com.br
 * 
 * Jonathas Eide Fujii
 * jonathasfujii@gmail.com
 * Criado: 23/09/2017
 * Atualizado: 23/09/2017
 * 
 * Arduino IDE v1.8.0
 * 
 * Interruptor Conectado modulo 002
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/
#include <OneWire.h>
#include <DallasTemperature.h>


const byte pinLedEsp = 2;

//// WIFI ////
const char* ssid = "";
const char* password = "";

//// MQTT ////
const char* mqtt_server = "";
const char* mqtt_username = "";
const char* mqtt_password = "";
long lastTimeMqtt = 60001;
const char* client_id = "esp-01-icm02"; // Must be unique on the MQTT network
const char* start_state_topic = "casa/icm02/start";
const char* rele1_state_topic = "casa/icm02/rele1";
const char* rele1_set_topic = "casa/icm02/rele1/set";
const char* rele2_state_topic = "casa/icm02/rele2";
const char* rele2_set_topic = "casa/icm02/rele2/set";
const char* on_cmd = "ON";
const char* off_cmd = "OFF";

WiFiClient espClient;
PubSubClient client(espClient);

//// WIFI ////
long lastTimeWifi = 60001;

//// Atuadores Relay ////
const byte pinRele1 = 0;
const byte pinRele2 = 2;

//// Botão ////
const int debouncerTime = 200;

const byte pinBotao1 = 1;
const byte pinBotao2 = 3;

byte readingBotao1 = HIGH;
byte readingBotao2 = HIGH;

byte botao1State = HIGH;
byte botao2State = HIGH;

byte botao1OldState = HIGH;
byte botao2OldState = HIGH;

long debounceTimeBotao1 = 0;
long debounceTimeBotao2 = 0;



