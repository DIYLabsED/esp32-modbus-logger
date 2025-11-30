#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include <credentials.hpp>


AsyncWebServer asyncServer(80);


void apiRebootESP(AsyncWebServerRequest* request);


void setup(){

  Serial.begin(115200);

  Serial.println("Attempting to connect to " + String(WIFI_SSID) + " with password " + String(WIFI_PASSWORD));
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){

    Serial.println("Awaiting connection");
    delay(500);

  }

  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());

  asyncServer.on("/api/admin/reboot", HTTP_GET, apiRebootESP).setAuthentication(API_USERNAME, API_PASSWORD);
  asyncServer.begin();

}

void loop(){

}

void apiRebootESP(AsyncWebServerRequest* request){

  ESP.restart();

}