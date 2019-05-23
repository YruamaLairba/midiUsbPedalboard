#ifndef SETUP_H
#define SETUP_H
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <Arduino.h> // for A0 - A5 pin name
DIAGNOSTIC_POP

//footswitch
const uint8_t nbFs = 4;
const uint8_t fsPins[] = {9, 10, 11, 12}; //footswitch input pin
const uint8_t fsLedPins[] = {A3, A2, A1, A0};//footswitch led output pin

//expression pedal
const uint8_t nbExp = 1;
const uint8_t expPins[] = {A5};

//OLED display
const uint8_t displayCs = 4;
const uint8_t displayDc = 3;
const uint8_t displayReset = 2;

//rotary coder
const uint8_t rotaryPinA = 8;
const uint8_t rotaryPinB = 7;

//ok and cancel buttons
const uint8_t buttonOkPin = 6;
const uint8_t buttonCancelPin = 5;

#endif //SETUP_H
