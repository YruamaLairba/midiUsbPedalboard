#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//OLED screen pinout
#define DISPLAY_CS     4
#define DISPLAY_DC     5
#define DISPLAY_RESET  6

extern Adafruit_SSD1306 display;

#endif //DISPLAY
