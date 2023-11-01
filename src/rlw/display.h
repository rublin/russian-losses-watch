#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <U8g2_for_Adafruit_GFX.h>
#include <SPI.h>
#include "wifi.h"

#include <Fonts/FreeMonoBold12pt7b.h>
// #include "Fonts/FreeSerif5pt7b.h"

#define VERSION "v0.0.24"

// ST7735 TFT module connections
#define TFT_RST D4 
#define TFT_CS D3  
#define TFT_DC D2   

extern Adafruit_ST7735 tft;
extern U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

void showTime();
void displayIco1();
void displayLosses1();
void displayLosses2();
void displayStartLogo();
void printText(char* text, uint16_t color);
String dBmtoPercentage(int dBm);
void drawCentreString(const String& text, int y, int size = 2);
void drawTime(String time, bool hide);
void drawWarDay(String text);
void drawWiFiParams(String text);
String getIncreaseLine();
void displayWiFiConnected();
void displayWiFiConfiguration();
int calcXcenter(int w);

#endif