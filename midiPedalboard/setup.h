#ifndef SETUP_H
#define SETUP_H
#include <Arduino.h> // for A0 - A5 pin name

//footswitch
extern const uint8_t nbFs;
extern const uint8_t fsPins[]; 
extern const uint8_t fsLedPins[];

//expression pedal
extern const uint8_t nbExp;
extern const uint8_t expPins[];

//OLED display
extern const uint8_t;
extern const uint8_t;
extern const uint8_t;

//rotary coder
extern const uint8_t rotaryPinA;
extern const uint8_t rotaryPinB;

//ok and cancel buttons
extern const uint8_t buttonOkPin;
extern const uint8_t buttonCancelPin;

#endif //SETUP_H
