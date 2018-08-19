#include "push_button.h"

PushButton::PushButton(uint8_t pin)
  : pin_(pin)
  , val_(PushButtonVal::none)
  , old_pin_val_(HIGH)
{
  pinMode(pin_, INPUT_PULLUP);
}

uint8_t PushButton::read()
{
  uint8_t cur_pin_val = digitalRead(pin_);
  unsigned long cur_millis = millis();
  val_ = PushButtonVal::none;
  if( cur_millis - debounce_millis_ >= debounceTime_)
  {
    if(old_pin_val_ != cur_pin_val)
    {
      if (cur_pin_val == LOW)
      {
        val_ = PushButtonVal::pressed;
      }
      else
      {
        val_ = PushButtonVal::depressed;
      }
    }
    old_pin_val_ = cur_pin_val;
    debounce_millis_ = cur_millis;
  }
  return val_;
}
