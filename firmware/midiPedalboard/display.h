#ifndef DISPLAY_H
#define DISPLAY_H

#include "setup.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <SPI.h>
#include <Wire.h>
#include <SSD1306AsciiSpi.h>
DIAGNOSTIC_POP

extern SSD1306AsciiSpi display;

#endif //DISPLAY
