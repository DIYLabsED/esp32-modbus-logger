#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

enum APIPermissionLevel{

  API_PERMISSION_ADMIN,
  API_PERMISSION_GENERAL

};

struct APIUser{

  String username;
  String password;
  APIPermissionLevel level;

};

struct APIEndpoint{

  String url;
  ArRequestHandlerFunction handler;
  APIPermissionLevel level;

};