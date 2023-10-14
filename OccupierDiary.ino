#include <Arduino.h>
#include "display.h"

const int SECONDS_IN_HOUR = 3600;

void setup() {
  Serial.begin(115200);
  tft.initR(INITR_GREENTAB);
  // tft.drawBitmap(0,0,trident,128,160,ST7735_CYAN);
  // delay(1000);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  u8g2_for_adafruit_gfx.begin(tft);
  wm.setBreakAfterConfig(true);

  bool res = wm.autoConnect("GloryToUkraine");

  if (!res) {
    Serial.println("Failed to connect");
    displayWiFiConfiguration();
    for (int i = 0; i <= 10; i++) {
      delay(60000);
      if (WiFi.reconnect()) {
        break;
      }
    }
    ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    displayWiFiConnected();
  }

  setupDateTime();
  getEnemyLosses();
}

void loop() {
  if (!WiFi.isConnected()) {
    WiFi.reconnect();
  }

  time_t now = DateTime.now();
  if ((now - lastUpdated) > SECONDS_IN_HOUR) {
    getEnemyLosses();
  }

  showTime();
  displayLosses1();
  showTime();
  displayLosses2();
}
