#include "footswitch.h"
#include "controller_system.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

void Footswitch::midi_send(uint8_t val)
{
  uint8_t usb_header = 0x0B;
  uint8_t status = 0xB0|pt_controller_system_->get_midi_channel();
  uint8_t data0 = get_command();
  uint8_t data1 = val;
  Serial1.write(status);
  Serial1.write(data0);
  Serial1.write(data1);
  midiEventPacket_t event = {
    usb_header,
    status,
    data0,
    data1,
  };
  MidiUSB.sendMIDI(event);
  Serial1.flush();
  MidiUSB.flush();
}

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

void Footswitch::setup(
    uint8_t fs_pin, uint8_t led_pin, ControllerSystem* pt_controller_system)
{
  fs_pin_= fs_pin;
  led_pin_ = led_pin;
  pinMode(led_pin_, OUTPUT);
  pinMode(fs_pin_, INPUT_PULLUP);
  pt_controller_system_ = pt_controller_system;
}

uint8_t Footswitch::get_command()
{
  return command_;
}

void Footswitch::set_command(uint8_t command)
{
  command_ = command;
  if (command_ > 127) command_ = 0;
}

uint8_t Footswitch::get_mode()
{
  return mode_;
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

void Footswitch::process()
{
  uint8_t cur_fs_pin_val= digitalRead(fs_pin_);
  unsigned long cur_millis = millis();

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
              digitalWrite(led_pin_, HIGH);
              fs_val_ = 1;
              midi_send(127);
            }
            else
            {
              digitalWrite(led_pin_, LOW);
              fs_val_ = 0;
              midi_send(0);
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
          digitalWrite(led_pin_, LOW);
          midi_send(0);
        }
        //on release
        else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
        {
          debounce_millis_ = cur_millis;
          digitalWrite(led_pin_, HIGH);
          midi_send(127);
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
          digitalWrite(led_pin_, HIGH);
          midi_send(127);
        }
        //on release
        else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
        {
          debounce_millis_ = cur_millis;
          digitalWrite(led_pin_, LOW);
          midi_send(0);
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
          digitalWrite(led_pin_, HIGH);
          led_millis_ = cur_millis;
          midi_send(0);
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
          digitalWrite(led_pin_, HIGH);
          led_millis_ = cur_millis;
          midi_send(127);
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
}

