#include <Arduino.h>
#include "display.h"

const int SECONDS_IN_HOUR = 3600;

void setup() {
  Serial.begin(115200);
  tft.initR(INITR_GREENTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  u8g2_for_adafruit_gfx.begin(tft);

  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT);
  wm.setWiFiAutoReconnect(true);
  wm.setConfigPortalTimeoutCallback(configPortalTimeoutCallback);
  wm.setShowInfoUpdate(true);

  bool res = wm.autoConnect("GloryToUkraine");

  if (!res) {
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

void loop() {
  wm.process();

  if (WiFi.isConnected()) {
    time_t now = DateTime.now();
    if ((now - lastUpdated) > SECONDS_IN_HOUR) {
      getEnemyLosses();
    }

    showTime();
    displayLosses1();
    showTime();
    displayLosses2();
  } 

}
