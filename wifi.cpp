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
