#include <ESPAsyncWebServer.h>

#include <WiFi.h>
#include "server_app.hpp"

AsyncWebServer* web_server;

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void server_app::start(){
  web_server = new AsyncWebServer(80);
  //web_server->serveStatic("/", SPIFFS, "/www/");
  web_server->on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "{the config will be parsed}");
    });
  web_server->onNotFound(notFound);
  web_server->begin();
}

void server_app::stop(){
  delete web_server;
}
