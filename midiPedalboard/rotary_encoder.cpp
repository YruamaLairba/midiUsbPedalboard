#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(int pin_a, int pin_b)
  : pin_a_(pin_a)
  , pin_b_(pin_b)
  , old_enc_a_(0)
  , old_enc_b_(0)
{
  pinMode(pin_a_, INPUT_PULLUP);
  pinMode(pin_b_, INPUT_PULLUP);
}

int RotaryEncoder::read()
{
  bool enc_a = digitalRead(pin_a_);
  bool enc_b = digitalRead(pin_b_);
  int returnVal = 0;

  //this code is for half cycle per indent rotary encoder
  if((!old_enc_a_ && !old_enc_b_ && !enc_a && enc_b) ||
    (old_enc_a_ && old_enc_b_ && enc_a && !enc_b)) 
  {
    returnVal = -1;
  }
  else if ((!old_enc_a_ && !old_enc_b_ && enc_a && !enc_b) ||
    (old_enc_a_ && old_enc_b_ && !enc_a && enc_b))
  {
    returnVal = 1;
  }

  old_enc_a_ = enc_a;
  old_enc_b_ = enc_b;
  return returnVal;
}
