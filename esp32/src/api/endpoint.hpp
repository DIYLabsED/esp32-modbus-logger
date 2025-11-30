#pragma once

#include <ESPAsyncWebServer.h>

enum APIPermissionLevel{

  API_PERMISSION_UNKNOWN,
  API_PERMISSION_GENERAL,
  API_PERMISSION_ADMIN

};

struct APIUser{

  const char* username;
  const char* password;
  APIPermissionLevel level;

};

struct APIEndpoint{

  const char* url;
  ArRequestHandlerFunction handler;
  APIPermissionLevel level;

};