#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include <credentials.hpp>


AsyncWebServer asyncServer(80);


void apiRebootESP(AsyncWebServerRequest* request);
void apiBlinkLED(AsyncWebServerRequest* request);


void setup(){

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Attempting to connect to " + String(WIFI_SSID) + " with password " + String(WIFI_PASSWORD));
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){

    Serial.println("Awaiting connection");
    delay(500);

  }

  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());

  asyncServer.on("/api/admin/reboot", HTTP_GET, apiRebootESP).setAuthentication(API_ADMIN_USERNAME, API_ADMIN_PASSWORD);
  asyncServer.on("/api/general/blink", HTTP_GET, apiBlinkLED).setAuthentication(API_GENERAL_USERNAME, API_GENERAL_PASSWORD);
  asyncServer.begin();

}

void loop(){

}

void apiRebootESP(AsyncWebServerRequest* request){

  ESP.restart();

}

void apiBlinkLED(AsyncWebServerRequest* request){

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

}