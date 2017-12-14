void mqtt_loop(){
  //// MQTT ////
  if (!client.connected() && millis() - lastTimeMqtt > 30000) {
    reconnect_mqtt();
    lastTimeMqtt = millis();
  }
  
  if (client.connected())
    client.loop();
}

void reconnect_mqtt() {
     if (client.connect(client_id, mqtt_username, mqtt_password)) {
      //Serial.println("connected");
      client.subscribe(rele1_set_topic);
      client.subscribe(rele2_set_topic);

      char buffer[100];
      sprintf(buffer, "{\"client_id\":\"%s\",\"ip\":\"%s\",\"t.wifi\":\"%u\",\"m.wifi\":\"%u\",\"t.mqtt\":\"%u\",\"m.mqtt\":\"%u\"}", client_id, WiFi.localIP().toString().c_str(), tentativaWifi, lastTimeWifi, tentativaMqtt, lastTimeMqtt);
      client.publish(start_state_topic, buffer);
      tentativaMqtt = 1;
    } else {
      tentativaMqtt++;
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print(topic);
  
  if (strcmp(topic,rele1_set_topic)==0){//// Rele 1 ////
      char msg[length];
      snprintf(msg, length+1, "%s", payload);
      if (strcmp(msg,on_cmd)==0) { 
        digitalWrite(pinRele1, LOW);   
        client.publish(rele1_state_topic, on_cmd);
      } else {
        digitalWrite(pinRele1, HIGH);   
        client.publish(rele1_state_topic, off_cmd);
      }
  } else if (strcmp(topic,rele2_set_topic)==0){//// Rele 2 ////
      char msg[length];
      snprintf(msg, length+1, "%s", payload);
      if (strcmp(msg,on_cmd)==0) { 
        digitalWrite(pinRele2, LOW);   
        client.publish(rele2_state_topic, on_cmd);
      } else {
        digitalWrite(pinRele2, HIGH);   
        client.publish(rele2_state_topic, off_cmd);
      }
  } 
}



