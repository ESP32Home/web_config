#include <Arduino.h>
#include <WiFi.h>

#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <ArduinoJson.h>
#include "server_app.hpp"

DynamicJsonDocument config(5*1024);//5 KB

server_app server;

void configModeCallback(AsyncWiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

String get_config(){
  String result;
  serializeJson(config, result);
  return result;
}

void set_config(String request){
  DynamicJsonDocument new_config(5*1024);
  deserializeJson(new_config, request);
  //TODO here update config with new_config
}

void wifi_setup(){
  AsyncWebServer server(80);
  DNSServer dns;
  AsyncWiFiManager wifiManager(&server,&dns);

  wifiManager.setAPCallback(configModeCallback);

  if(!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");

    ESP.restart();
    delay(1000);
  }
  Serial.println("WiFi connected");

}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  wifi_setup();

  server.start();

}

void loop() {
  delay(10000);
}

