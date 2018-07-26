#include "footswitch.h"

Footswitch::Footswitch()
  : command_(0)
  , mode_(fsMode::toggle_off)
  , fs_pin_(0)
  , led_pin_(0)
  , old_fs_pin_val_(HIGH)
  , fs_val_(0)
  , led_millis_(0)
  , debounce_millis_(0)
{}

void Footswitch::setup(uint8_t fs_pin, uint8_t led_pin)
{
  fs_pin_= fs_pin;
  led_pin_ = led_pin;
  pinMode(led_pin_, OUTPUT);
  pinMode(fs_pin_, INPUT_PULLUP);
}

void Footswitch::set_command(uint8_t command)
{
  command_ = command;
  if (command_ > 127) command_ = 0;
}

void Footswitch::set_mode(uint8_t mode)
{
  mode_ = mode;
  if (mode_ > fsMode::MAX) mode_ = fsMode::toggle_off;
  switch(mode_)
  {
    case fsMode::toggle_off:
      fs_val_=0;
      digitalWrite(led_pin_, LOW);
      break;
    case fsMode::toggle_on:
      fs_val_=1;
      digitalWrite(led_pin_, HIGH);
      break;
    case fsMode::momentary_off:
      digitalWrite(led_pin_, HIGH);
      break;
    case fsMode::momentary_on:
      digitalWrite(led_pin_, LOW);
      break;
    case fsMode::single_off:
      digitalWrite(led_pin_, LOW);
      break;
    case fsMode::single_on:
      digitalWrite(led_pin_, LOW);
      break;
  }
}

FsConfig Footswitch::get_config()
{
  FsConfig res;
  res.command = get_command();
  res.mode = get_mode();
  return res;
}

void Footswitch::set_config(FsConfig conf)
{
  set_command(conf.command);
  set_mode(conf.mode);
}

int8_t Footswitch::read()
{
  uint8_t cur_fs_pin_val= digitalRead(fs_pin_);
  unsigned long cur_millis = millis();
  int8_t result = -1;

  switch(mode_)
  {
    case fsMode::toggle_off:
    case fsMode::toggle_on:
      {
        if( cur_millis - debounce_millis_ >= debounceTime_)
        {
          //deboucing
          if(cur_fs_pin_val != old_fs_pin_val_)
          {
            debounce_millis_ = cur_millis;
          }
          //on press
          if(cur_fs_pin_val == LOW && old_fs_pin_val_ == HIGH)
          {
            if(fs_val_==0)
            {
              result = 127;
              digitalWrite(led_pin_, HIGH);
              fs_val_ = 1;
            }
            else
            {
              result = 0;
              digitalWrite(led_pin_, LOW);
              fs_val_ = 0;
            }
          }
        }
        break;
      }
    case fsMode::momentary_off:
      if( cur_millis - debounce_millis_ >= debounceTime_)
      {
        //on press
        if(cur_fs_pin_val == LOW && old_fs_pin_val_ == HIGH)
        {
          debounce_millis_ = cur_millis;
          result = 0;
          digitalWrite(led_pin_, LOW);
        }
        //on release
        else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
        {
          debounce_millis_ = cur_millis;
          result = 127;
          digitalWrite(led_pin_, HIGH);
        }
      }
      break;
    case fsMode::momentary_on:
      if( cur_millis - debounce_millis_ >= debounceTime_)
      {
        //on press
        if(cur_fs_pin_val == LOW && old_fs_pin_val_ == HIGH)
        {
          debounce_millis_ = cur_millis;
          result = 127;
          digitalWrite(led_pin_, HIGH);
        }
        //on release
        else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
        {
          debounce_millis_ = cur_millis;
          result = 0;
          digitalWrite(led_pin_, LOW);
        }
      }
      break;
    case fsMode::single_off:
      if( cur_millis - debounce_millis_ >= debounceTime_)
      {
        //deboucing
        if(cur_fs_pin_val != old_fs_pin_val_)
        {
          debounce_millis_ = cur_millis;
        }
        //on press
        if(cur_fs_pin_val == LOW && old_fs_pin_val_ == HIGH)
        {
          result = 0;
          digitalWrite(led_pin_, HIGH);
          led_millis_ = cur_millis;
        }
      }
      //when led_millis_ timeout
      if(cur_millis - led_millis_ > ledTime_)
      {
        digitalWrite(led_pin_, LOW);
      }
      break;
    case fsMode::single_on:
      if( cur_millis - debounce_millis_ >= debounceTime_)
      {
        //deboucing
        if(cur_fs_pin_val != old_fs_pin_val_)
        {
          debounce_millis_ = cur_millis;
        }
        //on press
        if(cur_fs_pin_val == LOW && old_fs_pin_val_ == HIGH)
        {
          result = 127;
          digitalWrite(led_pin_, HIGH);
          led_millis_ = cur_millis;
        }
      }
      //when led_millis_ timeout
      if(cur_millis - led_millis_ > ledTime_)
      {
        digitalWrite(led_pin_, LOW);
      }
    break;
  }
  old_fs_pin_val_ = cur_fs_pin_val;
  return result;
}

