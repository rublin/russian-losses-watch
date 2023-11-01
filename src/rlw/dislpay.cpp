#include "display.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

const int RSSI_MAX = -50;
const int RSSI_MIN = -100;
const int PIXEL_SHIFT = 8;

const char units_matrix[15][30] = { "personnel_units", "tanks", "armoured_fighting_vehicles", "artillery_systems", "mlrs", "aa_warfare_systems", "planes", "helicopters", "vehicles_fuel_tanks", "warships_cutters", "cruise_missiles", "uav_systems", "special_military_equip", "atgm_srbm_systems", "submarines" };
const char unit_names_matrix[15][30] = { "ос.складу", "танків", "ББМ", "арт.систем", "РСЗВ", "ППО", "літаків", "гелікоптерів", "авт.техніки", "кораблів", "крил.ракет", "БпЛА", "спец.техніки", "рак.комплеків", "підв.човнів" };

void showTime() {
  DateTimeParts p = DateTime.getParts();
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  drawCentreString(DateTime.format("%d %b  %a"), 5);

  tft.fillRect(10, 25, 28, 45, 0xC618);
  tft.fillRect(42, 25, 28, 45, 0xC618);
  tft.fillRect(93, 25, 28, 45, 0xC618);
  tft.fillRect(125, 25, 28, 45, 0xC618);

  String time = DateTime.format(DateFormatter::TIME_ONLY).substring(0, 5);
  drawTime(time, false);
  drawWarDay("War day: " + String(currentDay));

  // 20 seconds
  for (int i = 0; i < 200; i++) {

    // half a second
    if ((i % 5) == 0) {
      int j = (i / 5) % 2;
      if (j == 0) {
        drawTime(time, true);
      } else {
        drawTime(time, false);
      }
    }

    // 5 seconds
    if ((i % 50) == 0) {
      int j = (i / 50) % 2;
      if (j == 0) {
        drawWiFiParams("WiFi: " + WiFi.SSID().substring(0, 10) + " " + dBmtoPercentage(WiFi.RSSI()) + " " + VERSION);
      } else {
        drawWiFiParams("Local IP: " + WiFi.localIP().toString() + " v0.0." + VERSION);
      }
    }

    tft.fillRect(0, 75, 160, 18, 0x3800);
    u8g2_for_adafruit_gfx.setFont(u8g2_font_9x15_t_cyrillic);
    u8g2_for_adafruit_gfx.setCursor(0 - i * PIXEL_SHIFT, 88);
    u8g2_for_adafruit_gfx.print(getIncreaseLine());

    delay(100);
  }
}

void drawWarDay(String text) {
  tft.fillRect(0, 95, 160, 20, ST7735_BLACK);
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  drawCentreString(text, 95);
}

void drawWiFiParams(String text) {
  tft.fillRect(0, 115, 160, 10, ST7735_BLACK);
  u8g2_for_adafruit_gfx.setForegroundColor(ST77XX_WHITE);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_5x8_t_cyrillic);
  int width = u8g2_for_adafruit_gfx.getUTF8Width(text.c_str());
  u8g2_for_adafruit_gfx.setCursor(calcXcenter(width), 125);
  u8g2_for_adafruit_gfx.print(text);
}

void displayWiFiConnected() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);

  tft.setCursor(0, 10);
  tft.print("WiFi status:");
  tft.setCursor(0, 70);
  tft.print("WiFi network:");

  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  drawCentreString("Connected!", 40);
  drawCentreString(WiFi.SSID(), 100);

  delay(5000);
}

void displayWiFiConfiguration() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.setCursor(0, 10);
  tft.print("WiFi status:");
  tft.setTextColor(0x2015);
  drawCentreString("NOT connected", 35);

  u8g2_for_adafruit_gfx.setForegroundColor(ST77XX_WHITE);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_5x8_t_cyrillic);
  u8g2_for_adafruit_gfx.setCursor(0, 80);
  u8g2_for_adafruit_gfx.print("Connect to AP: GloryToUkraine");
  u8g2_for_adafruit_gfx.setCursor(0, 100);
  u8g2_for_adafruit_gfx.print("Open 192.168.4.1 in your browser");
  u8g2_for_adafruit_gfx.setCursor(0, 120);
  u8g2_for_adafruit_gfx.print("You have " + String(CONFIG_PORTAL_TIMEOUT / 60) + " minutes to configure");

  delay(5000);
}

void displayIco1() {

  tft.fillScreen(ST77XX_WHITE);
  // tft.drawRGBBitmap(0,0,people);
  // tft.drawRGBBitmap(0,80,bbm);
  // tft.drawBitmap(64, 0, tank, 80, 34, ST77XX_BLUE);
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

  u8g2_for_adafruit_gfx.setFont(u8g2_font_9x15_t_cyrillic);

  u8g2_for_adafruit_gfx.setCursor(0, 15);
  u8g2_for_adafruit_gfx.print("Ос. склад: " + getValue("personnel_units"));
  u8g2_for_adafruit_gfx.setCursor(0, 30);
  u8g2_for_adafruit_gfx.print("Танки:     " + getValue("tanks"));
  u8g2_for_adafruit_gfx.setCursor(0, 45);
  u8g2_for_adafruit_gfx.print("ББМ:       " + getValue("armoured_fighting_vehicles"));
  u8g2_for_adafruit_gfx.setCursor(0, 60);
  u8g2_for_adafruit_gfx.print("Арт.сист:  " + getValue("artillery_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 75);
  u8g2_for_adafruit_gfx.print("РСЗВ:      " + getValue("mlrs"));
  u8g2_for_adafruit_gfx.setCursor(0, 90);
  u8g2_for_adafruit_gfx.print("ППО:       " + getValue("aa_warfare_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 105);
  u8g2_for_adafruit_gfx.print("Літаки:    " + getValue("planes"));
  u8g2_for_adafruit_gfx.setCursor(0, 120);
  u8g2_for_adafruit_gfx.print("Гелікопт.: " + getValue("helicopters"));

  delay(5000);
}

String getIncreaseLine() {
  String buffer = String("     ");
  String result = String("За минулу ") + currentDay + " добу знищено: ";

  for (int i = 0; i < 15; i++) {
    int unit = getIncrease(units_matrix[i]);
    if (unit > 0) {
      if (i > 0) {
        result = result + ", ";
      }
      result = result + unit_names_matrix[i] + " " + unit;
    }
  }

  return buffer + result + buffer + result;
}

void displayLosses2() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_9x15_t_cyrillic);
  tft.fillRect(0, 5, 160, 12, 0x10A2);
  tft.fillRect(0, 35, 160, 12, 0x10A2);
  tft.fillRect(0, 65, 160, 12, 0x10A2);
  tft.fillRect(0, 95, 160, 12, 0x10A2);

  u8g2_for_adafruit_gfx.setCursor(0, 15);
  u8g2_for_adafruit_gfx.print("Авто.техн: " + getValue("vehicles_fuel_tanks"));
  u8g2_for_adafruit_gfx.setCursor(0, 30);
  u8g2_for_adafruit_gfx.print("Кораблі:   " + getValue("warships_cutters"));
  u8g2_for_adafruit_gfx.setCursor(0, 45);
  u8g2_for_adafruit_gfx.print("Крил.рак.: " + getValue("cruise_missiles"));
  u8g2_for_adafruit_gfx.setCursor(0, 60);
  u8g2_for_adafruit_gfx.print("БпЛА:      " + getValue("uav_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 75);
  u8g2_for_adafruit_gfx.print("Спец.техн: " + getValue("special_military_equip"));
  u8g2_for_adafruit_gfx.setCursor(0, 90);
  u8g2_for_adafruit_gfx.print("Рак.компл: " + getValue("atgm_srbm_systems"));
  u8g2_for_adafruit_gfx.setCursor(0, 105);
  u8g2_for_adafruit_gfx.print("Підв.човн: " + getValue("submarines"));

  delay(5000);
}

void displayStartLogo() {
  tft.fillScreen(ST77XX_BLACK);
  // u8g2_for_adafruit_gfx.setFont(u8g2_font_5x8_t_cyrillic);
  // tft.fillRect(0, 0, 160, 64, ST77XX_BLUE);
  // tft.fillRect(0, 65, 160, 64, ST77XX_YELLOW);
  // u8g2_for_adafruit_gfx.setCursor(10, 32);
  // u8g2_for_adafruit_gfx.print("Слава Україні!");
  // u8g2_for_adafruit_gfx.setCursor(10, 96);
  // u8g2_for_adafruit_gfx.print("Героям слава!");
  // delay(2000);
  // tft.fillScreen(ST77XX_BLACK);
  // tft.fillRect(0, 0, 160, 64, ST77XX_RED);
  // // tft.fillRect(0, 65, 160, 64, ST77XX_YELLOW);
  // u8g2_for_adafruit_gfx.setCursor(10, 32);
  // u8g2_for_adafruit_gfx.print("Слава нації!");
  // u8g2_for_adafruit_gfx.setCursor(10, 96);
  // u8g2_for_adafruit_gfx.print("Смерть ворогам!");
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
  tft.setCursor(calcXcenter(w), y);
  tft.print(text);
}

void drawTime(String time, bool hide) {
  tft.setFont(&FreeMonoBold12pt7b);
  tft.setTextColor(0x2015);
  tft.setCursor(12, 60);
  tft.print(time);
  tft.setFont();
  if (hide) {
    tft.fillRect(75, 30, 15, 35, ST77XX_BLACK);
  }
}

int calcXcenter(int w) {
  return (160 - w) / 2;
}
