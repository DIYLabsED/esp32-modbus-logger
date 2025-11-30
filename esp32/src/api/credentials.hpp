#pragma once

#include <Arduino.h>
#include <vector>
#include "endpoint.hpp"

const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

std::vector<APIUser> apiUsers;

void initCredentials(){

  apiUsers.push_back({"admin", "admin", API_PERMISSION_ADMIN});
  apiUsers.push_back({"general", "general", API_PERMISSION_GENERAL});

}