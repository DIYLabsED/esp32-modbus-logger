#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "endpoint.hpp"
#include "credentials.hpp"

void initAuthentication(){

  initCredentials();

}

APIPermissionLevel getRequestLevel(AsyncWebServerRequest *request){

  for(APIUser user : apiUsers){

    if(request->authenticate(user.username, user.password)){

      return user.level;

    }

  }

  return API_PERMISSION_UNKNOWN;

}

void registerAPIEndpoint(AsyncWebServer *server, APIEndpoint &endpoint){

  server->on(endpoint.url, HTTP_GET, [endpoint](AsyncWebServerRequest *request){

      APIPermissionLevel requestLevel = getRequestLevel(request);

      if(requestLevel >= endpoint.level){   // Users can access endpoints with lower permissions than themselves

        endpoint.handler(request);

      }
      else{

        if(requestLevel == API_PERMISSION_UNKNOWN){

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