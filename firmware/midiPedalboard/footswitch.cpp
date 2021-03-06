#include "footswitch.h"
#include "midi_utils.h"
#include "controller_system.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

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

fsCmdTyp_t Footswitch::get_cmd_typ()
{
  return cmd_typ_;
}

void Footswitch::set_cmd_typ(fsCmdTyp_t cmd_typ)
{
  cmd_typ_ = cmd_typ;
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

fsMmc_t Footswitch::get_mmc()
{
  return static_cast<fsMmc_t>(command_);
}

void Footswitch::set_mmc(fsMmc_t mmc)
{
  command_ = static_cast<uint8_t>(mmc);
  if (command_ > static_cast<uint8_t>(fsMmc_t::MAX)) command_ = 0;
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
  res.cmd_typ = static_cast<uint8_t>(get_cmd_typ());
  res.command = get_command();
  res.mode = get_mode();
  return res;
}

void Footswitch::set_config(FsConfig conf)
{
  set_cmd_typ((conf.cmd_typ<=static_cast<uint8_t>(fsCmdTyp_t::MAX))?
      static_cast<fsCmdTyp_t>(conf.cmd_typ):fsCmdTyp_t::MIN);
  set_command(conf.command);
  set_mode(conf.mode);
}

void Footswitch::process_cc(uint8_t cur_fs_pin_val)
{
  unsigned long cur_millis = millis();
  uint8_t status = 0xB0|pt_controller_system_->get_midi_channel();
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
              midi_send_cvm(status,get_command(),127);
            }
            else
            {
              digitalWrite(led_pin_, LOW);
              fs_val_ = 0;
              midi_send_cvm(status,get_command(),0);
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
          midi_send_cvm(status,get_command(),0);
        }
        //on release
        else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
        {
          debounce_millis_ = cur_millis;
          digitalWrite(led_pin_, HIGH);
          midi_send_cvm(status,get_command(),127);
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
          midi_send_cvm(status,get_command(),127);
        }
        //on release
        else if(cur_fs_pin_val == HIGH && old_fs_pin_val_ == LOW)
        {
          debounce_millis_ = cur_millis;
          digitalWrite(led_pin_, LOW);
          midi_send_cvm(status,get_command(),0);
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
          midi_send_cvm(status,get_command(),0);
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
          midi_send_cvm(status,get_command(),127);
        }
      }
      //when led_millis_ timeout
      if(cur_millis - led_millis_ > ledTime_)
      {
        digitalWrite(led_pin_, LOW);
      }
    break;
  }
}

void Footswitch::process_pgm(uint8_t cur_fs_pin_val)
{
  unsigned long cur_millis = millis();
  uint8_t status = 0xC0|pt_controller_system_->get_midi_channel();
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
      midi_send_cvm(status,get_command());
    }
  }
  //when led_millis_ timeout
  if(cur_millis - led_millis_ > ledTime_)
  {
    digitalWrite(led_pin_, LOW);
  }
}

enum mmc_mode_t : uint8_t
{
  single,
  toggle
};

void Footswitch::process_mmc(uint8_t cur_fs_pin_val)
{
  unsigned long cur_millis = millis();
  MMC_CMD value_on;
  MMC_CMD value_off;
  mmc_mode_t mode;
  switch (get_mmc())
  {
    case fsMmc_t::play:
      mode=mmc_mode_t::single;
      value_on=MMC_CMD::PLAY;
      break;
    case fsMmc_t::play_stop:
      mode=mmc_mode_t::toggle;
      value_on=MMC_CMD::PLAY;
      value_off=MMC_CMD::STOP;
      break;
    case fsMmc_t::stop:
      mode=mmc_mode_t::single;
      value_on=MMC_CMD::STOP;
      break;
    case fsMmc_t::record_punch:
      mode=mmc_mode_t::single;
      value_on=MMC_CMD::RECORD_STROBE;
    case fsMmc_t::record_punch_stop:
      mode=mmc_mode_t::toggle;
      value_on=MMC_CMD::RECORD_STROBE;
      value_off=MMC_CMD::STOP;
      break;
    case fsMmc_t::pause:
      mode=mmc_mode_t::single;
      value_on=MMC_CMD::PAUSE;
      break;
    case fsMmc_t::fast_forward:
      mode=mmc_mode_t::single;
      value_on=MMC_CMD::FAST_FORWARD;
      break;
    case fsMmc_t::rewind:
      mode=mmc_mode_t::single;
      value_on=MMC_CMD::REWIND;
      break;
  }
  switch(mode)
  {
    case mmc_mode_t::single:
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
          midi_send_mmc_cmd(value_on);
        }
      }
      //when led_millis_ timeout
      if(cur_millis - led_millis_ > ledTime_)
      {
        digitalWrite(led_pin_, LOW);
      }
      break;
    case mmc_mode_t::toggle:
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
            midi_send_mmc_cmd(value_on);
          }
          else
          {
            digitalWrite(led_pin_, LOW);
            fs_val_ = 0;
            midi_send_mmc_cmd(value_off);
          }
        }
      }
      break;
  }
}

void Footswitch::reset()
{
  cmd_typ_ = fsCmdTyp_t::cc;
  command_ = 0;
  mode_ = 0;
  fs_val_= 0;
  digitalWrite(led_pin_, LOW);
}

void Footswitch::process()
{
  uint8_t cur_fs_pin_val= digitalRead(fs_pin_);
  switch(cmd_typ_)
  {
    case fsCmdTyp_t::cc:
      process_cc(cur_fs_pin_val);
      break;
    case fsCmdTyp_t::pgm:
      process_pgm(cur_fs_pin_val);
      break;
    case fsCmdTyp_t::mmc:
      process_mmc(cur_fs_pin_val);
      break;
  }
  old_fs_pin_val_ = cur_fs_pin_val;
}

