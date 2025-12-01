#pragma once

#include <Arduino.h>
#include <vector>
#include <AuthAPI.hpp>

const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

AuthAPIUser generalAPIUser = {"general", "general", 0};
AuthAPIUser adminAPIUser   = {"admin", "admin", 1};