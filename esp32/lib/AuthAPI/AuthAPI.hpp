#pragma once

#include <ESPAsyncWebServer.h>
#include <vector>

typedef int8_t AuthAPIPermissionLevel;
const AuthAPIPermissionLevel AUTHAPI_PERMISSION_ERROR = -1;

struct AuthAPIUser{

  const char *username;
  const char *password;
  AuthAPIPermissionLevel permissionLevel;

};

struct AuthAPIEndpoint{

  const char *url;
  ArRequestHandlerFunction handler;
  AuthAPIPermissionLevel permissionLevel; 

};

class AuthAPI{

public:
  AuthAPI(AsyncWebServer *server);
  void registerUser(AuthAPIUser user);
  void registerEndpoint(AuthAPIEndpoint endpoint);

private:
  AsyncWebServer *_server;
  std::vector<AuthAPIUser> _users;
  AuthAPIPermissionLevel _getClientLevel(AsyncWebServerRequest *request);

};