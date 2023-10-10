#include "wifi.h"

JSONVar currentResponse;
time_t lastUpdated;
WiFiClientSecure client;
WiFiManager wm;

const char* host = "russianwarship.rip";
const String url = "/api/v2/statistics/latest";

String getValueWithIncrease(String param) {
  int increase = (int)currentResponse["data"]["increase"][param];
  // Serial.println(increase);
  int val = (int)currentResponse["data"]["stats"][param];
  // Serial.println(val);
  if (increase > 0) {
    return String(val) + "  ( +" + increase + ")";
  }
  return String(val);
}

String getValue(String param) {
  return String((int)currentResponse["data"]["stats"][param]);
}

int getIncrease(String param) {
  int increase = (int)currentResponse["data"]["increase"][param];
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
          Serial.println(F("SSSSSSSSSSSSSSSSS"));
          String payload = https.getString();
          Serial.println(payload);
          currentResponse = JSON.parse(payload);
          // Serial.println(currentResponse);
          Serial.println(currentResponse["message"]);
          Serial.println(currentResponse["data"]["date"]);
          // Serial.println(currentResponse["data"]["stats"]["tanks"]);
          lastUpdated = DateTime.now();
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

void reconnect() {
  if (!WiFi.isConnected()) {
    for (int i = 0; i <= 10; i++) {
      delay(60000);
      WiFi.reconnect();
    }
    ESP.restart();
  }
}

/*void getEnemyLosses() {
  HTTPClient https;

  Serial.print("[HTTPS] begin...\n");
  if (https.begin(client, host, 443, url)) {
    Serial.print("[HTTPS] GET...\n");
    int httpCode = https.GET();

    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        // https.getStream();
        Serial.println(F("SSSSSSSSSSSSSSSSS"));
        String payload = https.getString();
        Serial.println(payload);
        currentResponse = JSON.parse(payload);
        // Serial.println(currentResponse);
        Serial.println(currentResponse["message"]);
        Serial.println(currentResponse["data"]["date"]);
        // Serial.println(currentResponse["data"]["stats"]["tanks"]);
        lastUpdated = DateTime.now();
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}*/
