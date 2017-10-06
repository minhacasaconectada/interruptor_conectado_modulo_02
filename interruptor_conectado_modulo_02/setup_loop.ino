void setup() {
 // Serial.begin(115200);
  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
//    delay(5000);
//    ESP.restart();
//  }

  
  //// Atuadores Relay ////
  pinMode(pinRele1, OUTPUT);
  digitalWrite(pinRele1, HIGH);
  pinMode(pinRele2, OUTPUT);
  digitalWrite(pinRele2, HIGH);
  
  //// Botão ////
  pinMode(pinBotao1, INPUT_PULLUP);
  pinMode(pinBotao2, INPUT_PULLUP);
      
  //// MQTT ////
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
  if(WiFi.waitForConnectResult() != WL_CONNECTED &&  millis() - lastTimeWifi > 30000 ){
    WiFi.begin(ssid, password);  
    lastTimeWifi = millis();
  }
  
  mqtt_loop();
  verifica_botao();
}
