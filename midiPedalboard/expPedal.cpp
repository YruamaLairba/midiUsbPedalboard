#include "expPedal.h"

ExpPedal::ExpPedal()
  : command_(0)
  , mode_(expMode::normal)
  , exp_pin_(0)
  , debounce_millis_(0)
{}

void ExpPedal::setup(uint8_t exp_pin)
{
  exp_pin_= exp_pin;
  pinMode(exp_pin_, INPUT);
  old_exp_val_ = analogRead(exp_pin_);
}

void ExpPedal::set_mode(uint8_t mode)
{
  mode_ = mode;
}

ExpConfig ExpPedal::get_config()
{
  ExpConfig res;
  res.command = get_command();
  res.mode = get_mode();
  return res;
}

void ExpPedal::set_config(ExpConfig conf)
{
  set_command(conf.command);
  set_mode(conf.mode);
}

int16_t ExpPedal::read()
{
  uint16_t cur_exp_val= analogRead(exp_pin_);
  unsigned long cur_millis = millis();
  int16_t result = -1;

  if (old_exp_val_ != cur_exp_val)
  {
    switch(mode_)
    {
      case expMode::normal:
      case expMode::reverse:
        result = cur_exp_val;
        break;
    }
    old_exp_val_ = cur_exp_val;
  }
  return result;
}

