#ifndef DISPLAY_H
#define DISPLAY_H

#include "setup.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
DIAGNOSTIC_POP


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

extern Adafruit_SSD1306 display;

#endif //DISPLAY
