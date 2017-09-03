#include "setup.h"

//footswitch
const uint8_t nbFs = 4;
const uint8_t fsPins[] = {9, 10, 11, 12}; //footswitch input pin
const uint8_t fsLedPins[] = {A0, A1, A2, A3};//footswitch led output pin

//expression pedal
const uint8_t nbExp = 1;
const uint8_t expPins[] = {A5};

//OLED display
const uint8_t displayCs = 4;
const uint8_t displayDc = 5;
const uint8_t displayReset = 6;

//rotary coder
const uint8_t rotaryPinA = 2;
const uint8_t rotaryPinB = 3;

//ok and cancel buttons
const uint8_t buttonOkPin = 7;
const uint8_t buttonCancelPin = 8;
