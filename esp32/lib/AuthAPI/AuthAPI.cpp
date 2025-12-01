#include <AuthAPI.hpp>

AuthAPI::AuthAPI(AsyncWebServer *server){

  _server = server;

}

AuthAPIPermissionLevel AuthAPI::_getClientLevel(AsyncWebServerRequest *request){

  for(AuthAPIUser user : _users){

    if(request->authenticate(user.username, user.password)){
      return user.permissionLevel;
    }

  }

  return AUTHAPI_PERMISSION_ERROR;

}

void AuthAPI::registerUser(AuthAPIUser user){

  _users.push_back(user);

}

void AuthAPI::registerEndpoint(AuthAPIEndpoint endpoint){

  _server->on(endpoint.url, HTTP_GET,

    [this, endpoint](AsyncWebServerRequest *request){

      AuthAPIPermissionLevel clientLevel = _getClientLevel(request);

      if(clientLevel >= endpoint.permissionLevel){
        
        endpoint.handler(request);

      }
      else{

        if(clientLevel == AUTHAPI_PERMISSION_ERROR){

          request->requestAuthentication();
          return;

        }
        else{

          request->send(403, "text/plain", "Insufficient permission to access this endpoint.");
          return;
          
        }

      }

    }

  );

}