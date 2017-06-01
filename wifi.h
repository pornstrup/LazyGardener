bool wifiReconnect(){
  if(WiFi.status() != WL_CONNECTED){
    digitalWrite(LED_INFO_PIN, LOW);
    
    #if defined(DEBUG)
      Serial.print(F("Connecting to "));
      Serial.print(WIFI_SSID);
    #endif
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    unsigned long now = millis();
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(250);
      #if defined(DEBUG)
        Serial.print(F("."));
      #endif

      if (millis() - now >= WIFI_CONNECTION_TIMEOUT) {
        #if defined(DEBUG)
          Serial.println(F("WiFi connection timeout, restarting..."));
        #endif
        ESP.restart();
        return false;
      }
    }
    
    #if defined(DEBUG)
      Serial.println(F("OK"));
    #endif

    // ArduinoOTA.setPort(3232);
    ArduinoOTA.setHostname(DEVICE_NAME);
    
    #if defined(DEBUG)
      ArduinoOTA.onStart([]() {
        Serial.println(F("Starting OTA"));
      });
      ArduinoOTA.onEnd([]() {
        Serial.println(F("\nEnd"));
      });
      ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      });
      ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println(F("Auth Failed"));
        else if (error == OTA_BEGIN_ERROR) Serial.println(F("Begin Failed"));
        else if (error == OTA_CONNECT_ERROR) Serial.println(F("Connect Failed"));
        else if (error == OTA_RECEIVE_ERROR) Serial.println(F("Receive Failed"));
        else if (error == OTA_END_ERROR) Serial.println(F("End Failed"));
      });
    #endif
    ArduinoOTA.begin();
  }
  return true;
}



