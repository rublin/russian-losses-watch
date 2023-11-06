#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "time.h"

extern String currentDate;
extern int currentDay;
extern JsonObject currentStats;
extern JsonObject currentIncrease;
extern time_t lastUpdated;
extern WiFiClientSecure client;
extern WiFiManager wm;
extern const long CONFIG_PORTAL_TIMEOUT;
extern const char* CONFIG_PORTAL_SSID;

void configureWiFiManager();
String getValueWithIncrease(String param);
String getValue(String param);
int getIncrease(String param);
void getEnemyLosses();

void configPortalTimeoutCallback();
void saveConfigCallback();

void readConfigFile();
void loadSavedParameters();

#endif