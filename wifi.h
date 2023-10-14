#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H

#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Arduino_JSON.h>
#include "time.h"

extern JSONVar currentResponse;
extern time_t lastUpdated;
extern WiFiClientSecure client;
extern WiFiManager wm;
extern const long CONFIG_PORTAL_TIMEOUT;

String getValueWithIncrease(String param);
String getValue(String param);
int getIncrease(String param);
void getEnemyLosses();
void configPortalTimeoutCallback();

#endif