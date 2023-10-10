#include "display.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

const int RSSI_MAX = -50;
const int RSSI_MIN = -100;

void showTime() {
  DateTimeParts p = DateTime.getParts();
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  drawCentreString(DateTime.format("%d %b  %a"), 5);

  // tft.setTextColor(ST77XX_GREEN, ST7735_BLACK);
  // drawCentreString(DateTime.format("%d %b  %a"), 76);

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  tft.setCursor(10, 95);
  tft.setTextSize(2);
  tft.print("War day: " + String((int)currentResponse["data"]["day"]));

  // tft.setFont(&FreeSerif5pt7b);
  // tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  // tft.setCursor(5, 125);
  // tft.setTextSize(1);

  // tft.print("WiFi: " + WiFi.SSID().substring(0, 10) + " " + dBmtoPercentage(WiFi.RSSI()) + " " + WiFi.localIP().toString());
  // tft.setFont();

  u8g2_for_adafruit_gfx.setForegroundColor(ST77XX_WHITE);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_5x8_t_cyrillic);
  u8g2_for_adafruit_gfx.setCursor(5, 125);
  u8g2_for_adafruit_gfx.print("WiFi: " + WiFi.SSID().substring(0, 10) + " " + dBmtoPercentage(WiFi.RSSI()) + " " + WiFi.localIP().toString());

  tft.fillRect(10, 25, 28, 45, 0xC618);
  tft.fillRect(42, 25, 28, 45, 0xC618);
  tft.fillRect(93, 25, 28, 45, 0xC618);
  tft.fillRect(125, 25, 28, 45, 0xC618);

  String time = DateTime.format(DateFormatter::TIME_ONLY).substring(0, 5);
  for (int i = 0; i < 10; i++) {
    drawTime(time);
  }
}

void displayIco1() {

  tft.fillScreen(ST77XX_WHITE);
  // tft.drawRGBBitmap(0,0,people);
  // tft.drawRGBBitmap(0,80,bbm);
  tft.drawBitmap(64, 0, tank, 80, 34, ST77XX_BLUE);
  // int h = 80, w = 50, row, col, buffidx = 0;
  // for (row = 0; row < h; row++) {    // For each scanline...
  //   for (col = 0; col < w; col++) {  // For each pixel...
  //     //To read from Flash Memory, pgm_read_XXX is required.
  //     //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
  //     tft.drawPixel(col, row, pgm_read_word(people + buffidx));
  //     buffidx++;
  //   }  // end pixel
  // }

  // delay(2000);
  // for (row = 0; row < h; row++) {    // For each scanline...
  //   for (col = 0; col < w; col++) {  // For each pixel...
  //     //To read from Flash Memory, pgm_read_XXX is required.
  //     //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
  //     tft.drawPixel(col, row, pgm_read_word(tank + buffidx));
  //     buffidx++;
  //   }  // end pixel
  // }
  delay(5000);
}

void displayLosses1() {
  tft.fillScreen(ST77XX_BLACK);

  tft.fillRect(0, 5, 160, 12, 0x10A2);
  tft.fillRect(0, 35, 160, 12, 0x10A2);
  tft.fillRect(0, 65, 160, 12, 0x10A2);
  tft.fillRect(0, 95, 160, 12, 0x10A2);

  u8g2_for_adafruit_gfx.setFont(u8g2_font_6x13_t_cyrillic);

  u8g2_for_adafruit_gfx.setCursor(0, 15);
  u8g2_for_adafruit_gfx.print("Ос. склад:          " + getValue("personnel_units"));
  u8g2_for_adafruit_gfx.setCursor(0, 30);
  u8g2_for_adafruit_gfx.print("Танки:              " + getValue("tanks"));
  u8g2_for_adafruit_gfx.setCursor(0, 45);
  u8g2_for_adafruit_gfx.print("Бой.машини:         " + getValue("armoured_fighting_vehicles"));
  u8g2_for_adafruit_gfx.setCursor(0, 60);
  u8g2_for_adafruit_gfx.print("Арт.системи:        " + getValue("artillery_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 75);
  u8g2_for_adafruit_gfx.print("РСЗВ:               " + getValue("mlrs"));
  u8g2_for_adafruit_gfx.setCursor(0, 90);
  u8g2_for_adafruit_gfx.print("ППО:                " + getValue("aa_warfare_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 105);
  u8g2_for_adafruit_gfx.print("Літаки:             " + getValue("planes"));
  u8g2_for_adafruit_gfx.setCursor(0, 120);
  u8g2_for_adafruit_gfx.print("Гелікоптери:        " + getValue("helicopters"));

  delay(5000);
  tft.fillRect(100, 0, 60, 128, ST77XX_BLACK);
  tft.fillRect(100, 5, 160, 12, 0x10A2);
  tft.fillRect(100, 35, 160, 12, 0x10A2);
  tft.fillRect(100, 65, 160, 12, 0x10A2);
  tft.fillRect(100, 95, 160, 12, 0x10A2);

  u8g2_for_adafruit_gfx.setCursor(0, 15);
  u8g2_for_adafruit_gfx.print("Ос. склад:          " + getIncrease("personnel_units"));
  u8g2_for_adafruit_gfx.setCursor(0, 30);
  u8g2_for_adafruit_gfx.print("Танки:              " + getIncrease("tanks"));
  u8g2_for_adafruit_gfx.setCursor(0, 45);
  u8g2_for_adafruit_gfx.print("Бой.машини:         " + getIncrease("armoured_fighting_vehicles"));
  u8g2_for_adafruit_gfx.setCursor(0, 60);
  u8g2_for_adafruit_gfx.print("Арт.системи:        " + getIncrease("artillery_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 75);
  u8g2_for_adafruit_gfx.print("РСЗВ:               " + getIncrease("mlrs"));
  u8g2_for_adafruit_gfx.setCursor(0, 90);
  u8g2_for_adafruit_gfx.print("ППО:                " + getIncrease("aa_warfare_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 105);
  u8g2_for_adafruit_gfx.print("Літаки:             " + getIncrease("planes"));
  u8g2_for_adafruit_gfx.setCursor(0, 120);
  u8g2_for_adafruit_gfx.print("Гелікоптери:        " + getIncrease("helicopters"));

  delay(5000);
}

String getIncreaseLine() {
  return "За минулу добу знищено ос.складу 579, танків 23, арт.систем 14, РСЗВ 2, БпЛА 4";
}

void displayLosses2() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_6x13_t_cyrillic);
  tft.fillRect(0, 5, 160, 12, 0x10A2);
  tft.fillRect(0, 35, 160, 12, 0x10A2);
  tft.fillRect(0, 65, 160, 12, 0x10A2);
  tft.fillRect(0, 95, 160, 12, 0x10A2);

  // tft.setFont();
  // tft.setFont(&FreeSans20pt7b);
  // tft.setTextColor(0x2015);
  // tft.setCursor(0, 15);
  // tft.print("Авто.техніка:       " + getValue("vehicles_fuel_tanks"));
  // tft.setFont();
  u8g2_for_adafruit_gfx.setCursor(0, 15);
  u8g2_for_adafruit_gfx.print("Авто.техніка:       " + getValue("vehicles_fuel_tanks"));
  u8g2_for_adafruit_gfx.setCursor(0, 30);
  u8g2_for_adafruit_gfx.print("Кораблі:            " + getValue("warships_cutters"));
  u8g2_for_adafruit_gfx.setCursor(0, 45);
  u8g2_for_adafruit_gfx.print("Крил.ракети:        " + getValue("cruise_missiles"));
  u8g2_for_adafruit_gfx.setCursor(0, 60);
  u8g2_for_adafruit_gfx.print("БпЛА:               " + getValue("uav_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 75);
  u8g2_for_adafruit_gfx.print("Спец.техніка:       " + getValue("special_military_equip"));
  u8g2_for_adafruit_gfx.setCursor(0, 90);
  u8g2_for_adafruit_gfx.print("Ракетні комплекси:  " + getValue("atgm_srbm_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 105);
  u8g2_for_adafruit_gfx.print("Підводні човни:     " + getValue("submarines"));

  delay(5000);
  tft.fillRect(100, 0, 60, 128, ST77XX_BLACK);
  tft.fillRect(0, 5, 160, 12, 0x10A2);
  tft.fillRect(0, 35, 160, 12, 0x10A2);
  tft.fillRect(0, 65, 160, 12, 0x10A2);
  tft.fillRect(0, 95, 160, 12, 0x10A2);

  u8g2_for_adafruit_gfx.setCursor(0, 15);
  u8g2_for_adafruit_gfx.print("Авто.техніка:       " + getIncrease("vehicles_fuel_tanks"));
  u8g2_for_adafruit_gfx.setCursor(0, 30);
  u8g2_for_adafruit_gfx.print("Кораблі:            " + getIncrease("warships_cutters"));
  u8g2_for_adafruit_gfx.setCursor(0, 45);
  u8g2_for_adafruit_gfx.print("Крил.ракети:        " + getIncrease("cruise_missiles"));
  u8g2_for_adafruit_gfx.setCursor(0, 60);
  u8g2_for_adafruit_gfx.print("БпЛА:               " + getIncrease("uav_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 75);
  u8g2_for_adafruit_gfx.print("Спец.техніка:       " + getIncrease("special_military_equip"));
  u8g2_for_adafruit_gfx.setCursor(0, 90);
  u8g2_for_adafruit_gfx.print("Ракетні комплекси:  " + getIncrease("atgm_srbm_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 105);
  u8g2_for_adafruit_gfx.print("Підводні човни:     " + getIncrease("submarines"));

  delay(5000);
}

void displayStartLogo() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_5x8_t_cyrillic);
  tft.fillRect(0, 0, 160, 64, ST77XX_BLUE);
  tft.fillRect(0, 65, 160, 64, ST77XX_YELLOW);
  u8g2_for_adafruit_gfx.setCursor(10, 32);
  u8g2_for_adafruit_gfx.print("Слава Україні!");
  u8g2_for_adafruit_gfx.setCursor(10, 96);
  u8g2_for_adafruit_gfx.print("Героям слава!");
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRect(0, 0, 160, 64, ST77XX_RED);
  // tft.fillRect(0, 65, 160, 64, ST77XX_YELLOW);
  u8g2_for_adafruit_gfx.setCursor(10, 32);
  u8g2_for_adafruit_gfx.print("Слава нації!");
  u8g2_for_adafruit_gfx.setCursor(10, 96);
  u8g2_for_adafruit_gfx.print("Смерть ворогам!");
  delay(2000);
}

/*
 * Written by Ahmad Shamshiri
  * with lots of research, this sources was used:
 * https://support.randomsolutions.nl/827069-Best-dBm-Values-for-Wifi 
 * This is approximate percentage calculation of RSSI
 * WiFi Signal Strength Calculation
 * Written Aug 08, 2019 at 21:45 in Ajax, Ontario, Canada
 */
String dBmtoPercentage(int dBm) {
  int quality;
  if (dBm <= RSSI_MIN) {
    quality = 0;
  } else if (dBm >= RSSI_MAX) {
    quality = 100;
  } else {
    quality = 2 * (dBm + 100);
  }
  return String(quality) + "%";
}

void printText(char* text, uint16_t color) {
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawCentreString(const String& text, int y, int size) {
  int x = 160;
  int16_t x1, y1;
  uint16_t w, h;
  tft.setTextSize(size);
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h);  //calc width of new string
  // Serial.println(String("x = ") + x + " y = " + y + " x1 = " + x1 + " y1 = " + y1 + " w = " + w + " h = " + h);
  // Serial.println(x - w / 2);
  tft.setCursor((x - w) / 2, y);
  tft.print(text);
}

void drawTime(String time) {
  tft.setFont(&FreeMonoBold12pt7b);
  tft.setTextColor(0x2015);
  tft.setCursor(12, 60);
  tft.print(time);
  tft.setFont();
  delay(1000);
  tft.fillRect(75, 30, 15, 35, ST77XX_BLACK);
  delay(1000);
}