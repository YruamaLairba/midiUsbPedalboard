#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>

class RotaryEncoder {
 public:
  RotaryEncoder(int pin_a, int pin_b);
  int read();
 private:
  int pin_a_, pin_b_; //pin used by the rotary encoder
  bool old_enc_a_, old_enc_b_; //old value of the pin
};

#endif //ROTARY_ENCODER_H
