#include <Arduino.h>
#include <WiFi.h>

#include <ESPWiFiConfig.h>

#include <ArduinoJson.h>
#include "server_app.hpp"

DynamicJsonDocument config(5*1024);//5 KB

server_app server;

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

void setup() {
  Serial.begin(115200);

  wifi_setup();

  server.start();

}

void loop() {
  delay(10000);
}

