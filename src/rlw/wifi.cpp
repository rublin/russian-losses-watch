#include "wifi.h"

String currentDate;
int currentDay;
JsonObject currentStats;
JsonObject currentIncrease;
time_t lastUpdated;
WiFiClientSecure client;
WiFiManager wm;

const char* host = "russianwarship.rip";
const String url = "/api/v2/statistics/latest";
const long CONFIG_PORTAL_TIMEOUT = 300;
const char* CONFIG_PORTAL_SSID = "GloryToUkraine";

WiFiManagerParameter custom_timeZone("timeZone", "timezone offset (like +2 or -8) or timezone name (like EST5) or POSIX TZ (for Kyiv EET-2EEST,M3.5.0/3,M10.5.0/4)", timeZone, 30);

void configureWiFiManager() {
  custom_timeZone.setValue(timeZone, 30);

  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT);
  wm.setWiFiAutoReconnect(true);

  wm.setConfigPortalTimeoutCallback(configPortalTimeoutCallback);
  //called when wifi settings have been changed and connection was successful ( or setBreakAfterConfig(true) )
  wm.setSaveConfigCallback(saveConfigCallback);
  // //called after AP mode and config portal has started
  // wm.setAPCallback(std::function<void(WiFiManager*)> func);
  // //called after webserver has started
  // wm.setWebServerCallback(std::function<void()> func);
  // //called when saving either params-in-wifi or params page
  wm.setSaveParamsCallback(saveConfigCallback);
  // //called when settings reset have been triggered
  // wm.setConfigResetCallback(std::function<void()> func);
  // //called when saving params-in-wifi or params before anything else happens (eg wifi)
  // wm.setPreSaveConfigCallback(std::function<void()> func);
  // //called when saving params before anything else happens
  // wm.setPreSaveParamsCallback(std::function<void()> func);
  // //called just before doing OTA update
  // wm.setPreOtaUpdateCallback(std::function<void()> func);

  wm.setShowInfoUpdate(true);
  wm.addParameter(&custom_timeZone);
}

String getValueWithIncrease(String param) {
  int increase = (int)currentIncrease[param];
  // Serial.println(increase);
  int val = (int)currentStats[param];
  // Serial.println(val);
  if (increase > 0) {
    return String(val) + "  ( +" + increase + ")";
  }
  return String(val);
}

String getValue(String param) {
  return String((int)currentStats[param]);
}

int getIncrease(String param) {
  int increase = (int)currentIncrease[param];
  if (increase > 0) {
    return increase;
  }
  return 0;
}

void getEnemyLosses() {
  if (WiFi.isConnected()) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    // client->setFingerprint(fingerprint_sni_cloudflaressl_com);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, host, 443, url)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);

          DynamicJsonDocument doc(1600);
          DeserializationError error = deserializeJson(doc, payload);

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
          } else {
            JsonObject data = doc["data"];

            const char* date = data["date"];  // "2023-10-17"
            int day = data["day"];

            currentDate = date;
            currentDay = day;
            currentStats = data["stats"];
            currentIncrease = data["increase"];

            lastUpdated = DateTime.now();
            Serial.println(currentDay);
          }
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  } else {
    WiFi.reconnect();
  }
}

void configPortalTimeoutCallback() {
  Serial.println("Configuration portal timeout callback started");
  ESP.restart();
}

void saveConfigCallback() {
  Serial.println("save config");
  loadSavedParameters();
  DynamicJsonDocument json(1024);
  json["timeZone"] = timeZone;

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  serializeJson(json, Serial);
  serializeJson(json, configFile);
  configFile.close();
  ESP.restart();
}

void readConfigFile() {
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if (!deserializeError) {
          Serial.println("\nparsed json");
          strcpy(timeZone, json["timeZone"]);
        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
}

void loadSavedParameters() {
  strcpy(timeZone, custom_timeZone.getValue());
  Serial.println("The values in the file are: ");
  Serial.println("\ttimeZone: " + String(timeZone));
}