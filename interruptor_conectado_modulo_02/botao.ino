void verifica_botao(){
  long now = millis();  

  readingBotao1 = digitalRead(pinBotao1);
  if(readingBotao1 != botao1OldState){
      debounceTimeBotao1 = now;
  }
  if(now - debounceTimeBotao1 > 50){
    if(readingBotao1 != botao1State){
      botao1State = readingBotao1;
      if(botao1State == LOW){
        if(digitalRead(pinRele1) == LOW){
          digitalWrite(pinRele1, HIGH);
          if(WiFi.waitForConnectResult() == WL_CONNECTED && client.connected())
            client.publish(rele1_state_topic, off_cmd);
        } else {
          digitalWrite(pinRele1, LOW);
          if(WiFi.waitForConnectResult() == WL_CONNECTED && client.connected())
            client.publish(rele1_state_topic, on_cmd);
        }
      }
    }
  }
  botao1OldState = readingBotao1;

  readingBotao2 = digitalRead(pinBotao2);
  if(readingBotao2 != botao2OldState){
      debounceTimeBotao2 = now;
  }
  if(now - debounceTimeBotao2 > 50){
    if(readingBotao2 != botao2State){
      botao2State = readingBotao2;
      if(botao2State == LOW){
        if(digitalRead(pinRele2) == LOW){
          digitalWrite(pinRele2, HIGH);
          if(WiFi.waitForConnectResult() == WL_CONNECTED && client.connected())
            client.publish(rele2_state_topic, off_cmd);
        } else {
          digitalWrite(pinRele2, LOW);
          if(WiFi.waitForConnectResult() == WL_CONNECTED && client.connected())
            client.publish(rele2_state_topic, on_cmd);
        }
      }
    }
  }
  botao2OldState = readingBotao2;
  
}



