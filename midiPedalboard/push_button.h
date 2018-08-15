#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "warnings.h"
#include <stdint.h>

DIAGNOSTIC_IGNORE_ALL
#include <Arduino.h>
DIAGNOSTIC_POP

struct PushButtonVal
{
  enum
  {
    none,
    pressed,
    depressed
  };
};

class PushButton
{
  private:
    static const unsigned long debounceTime_ = 100;
    unsigned long debounce_millis_;//for debouncing
    uint8_t pin_;
    uint8_t old_pin_val_;
    uint8_t val_;
  public:
    PushButton(uint8_t pin);
    uint8_t read();
};

#endif //PUSH_BUTTON_H 
