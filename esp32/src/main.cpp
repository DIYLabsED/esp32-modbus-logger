#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AuthAPI.hpp>
#include <WiFi.h>
#include <credentials.hpp>


AsyncWebServer asyncServer(80);
AuthAPI authAPI(&asyncServer);


void apiRebootESP(AsyncWebServerRequest* request);
void apiBlinkLED(AsyncWebServerRequest* request);

AuthAPIEndpoint rebootEndpoint = {"/api/reboot", apiRebootESP, 1};
AuthAPIEndpoint blinkEndpoint = {"/api/blink", apiBlinkLED, 0};


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

  authAPI.registerEndpoint(rebootEndpoint);
  authAPI.registerEndpoint(blinkEndpoint);
  authAPI.registerUser(generalAPIUser);
  authAPI.registerUser(adminAPIUser);

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