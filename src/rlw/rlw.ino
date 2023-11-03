#include <Arduino.h>
#include "display.h"

const int SECONDS_IN_HOUR = 3600;
const char* CONFIG_PORTAL_SSID = "GloryToUkraine";

#ifndef INITR
#define INITR INITR_BLACKTAB
#endif

void setup() {
  Serial.begin(115200);
  tft.initR(INITR);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  u8g2_for_adafruit_gfx.begin(tft);

  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT);
  wm.setWiFiAutoReconnect(true);
  wm.setConfigPortalTimeoutCallback(configPortalTimeoutCallback);
  wm.setShowInfoUpdate(true);

  if (drd.detectDoubleReset()) {
    wm.startConfigPortal(CONFIG_PORTAL_SSID);
    Serial.println("Double Reset Detected");
    displayWiFiConfiguration();
  } else {
    if (!wm.autoConnect(CONFIG_PORTAL_SSID)) {
      Serial.println("Failed to connect");
      displayWiFiConfiguration();
    } else {
      //if you get here you have connected to the WiFi
      Serial.println("connected...yeey :)");
      wm.setConnectTimeout(30);
      wm.setConnectRetries(5);

      displayWiFiConnected();
      setupDateTime();
      getEnemyLosses();
    }
  }
  drd.stop();
}

void loop() {
  wm.process();

  if (WiFi.isConnected()) {
    time_t now = DateTime.now();
    if ((now - lastUpdated) > SECONDS_IN_HOUR / 2) {
      getEnemyLosses();
    }

    showTime();
    displayLosses1();
    showTime();
    displayLosses2();
  }
}
