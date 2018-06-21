#include "footswitch.h"

Footswitch::Footswitch()
  : fs_pin_(0)
  , led_pin_(0)
  , old_fs_pin_val_(HIGH)
  , fs_val_(0)
{}

void Footswitch::setup(uint8_t fs_pin, uint8_t led_pin)
{
  fs_pin_= fs_pin;
  led_pin_ = led_pin;
  pinMode(fs_pin_, INPUT_PULLUP);
  pinMode(led_pin_, OUTPUT);
}

uint8_t Footswitch::read()
{
  uint8_t cur_fs_pin_val= digitalRead(fs_pin_);
  uint8_t result = 0;
  if(cur_fs_pin_val == LOW && old_fs_pin_val_ == HIGH)
  {
    result = 1;
    digitalWrite(led_pin_, HIGH);
  }
  else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
  {
    result = -1;
    digitalWrite(led_pin_, LOW);
  }

  old_fs_pin_val_ = cur_fs_pin_val;
  return result;
}

