#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#include <api/authentication.hpp>
#include <api/endpoint.hpp>

AsyncWebServer asyncServer(80);


void apiRebootESP(AsyncWebServerRequest* request);
void apiBlinkLED(AsyncWebServerRequest* request);

APIEndpoint rebootEndpoint = {"/api/reboot", apiRebootESP, API_PERMISSION_ADMIN};
APIEndpoint blinkEndpoint = {"/api/blink", apiBlinkLED, API_PERMISSION_GENERAL};


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

  initAuthentication();

  registerAPIEndpoint(&asyncServer, rebootEndpoint);
  registerAPIEndpoint(&asyncServer, blinkEndpoint);

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