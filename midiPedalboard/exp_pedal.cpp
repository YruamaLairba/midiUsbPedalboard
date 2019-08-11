#include "exp_pedal.h"
#include "midi_utils.h"
#include "controller_system.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

ExpPedal::ExpPedal()
  : command_(0)
  , mode_(expMode::normal)
  , exp_pin_(0)
  , change_delay_millis_(0)
{}

void ExpPedal::setup(uint8_t exp_pin, ControllerSystem* pt_controller_system)
{
  exp_pin_= exp_pin;
  pinMode(exp_pin_, INPUT);
  old_exp_val_ = analogRead(exp_pin_);
  pt_controller_system_ = pt_controller_system;
}

void ExpPedal::set_cmd_typ(expCmdTyp_t cmd_typ)
{
  cmd_typ_ = cmd_typ;
}


void ExpPedal::set_command(uint8_t command)
{
  command_ = command;
  if (command_ > 127) command_ = 0;
}

void ExpPedal::set_mode(uint8_t mode)
{
  mode_ = mode;
  if (mode_ > 127) mode_ = 0;
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

int16_t ExpPedal::get_raw_val(){return raw_exp_val_;}

int16_t ExpPedal::get_toes_val(){return toes_val_;}

void ExpPedal::set_toes_val(int16_t val){toes_val_ = val;}

int16_t ExpPedal::get_heel_val(){return heel_val_;}

void ExpPedal::set_heel_val(int16_t val){heel_val_ = val;}

void ExpPedal::reset()
{
  cmd_typ_ = expCmdTyp_t::none;
  command_ = 0;
  mode_ = 0;
}

void ExpPedal::process_cc(int16_t cur_exp_val)
{
  uint8_t status = 0xB0|pt_controller_system_->get_midi_channel();
  int16_t val;
  switch(mode_)
  {
    case expMode::normal:
      val = map(cur_exp_val,heel_val_,toes_val_,0,127);
      break;
    case expMode::reverse:
      val = map(cur_exp_val,heel_val_,toes_val_,127,0);
      break;
  }
  uint8_t cc_val = constrain(val,0,127);
  midi_send_cvm(status,get_command(),cc_val);
}

void ExpPedal::process_pb(int16_t cur_exp_val)
{
  uint8_t status = 0xE0|pt_controller_system_->get_midi_channel();
  int16_t pb_val;
      switch(mode_)
      {
        case expMode::normal:
          pb_val = map(cur_exp_val,heel_val_,toes_val_,0,16383);
          break;
        case expMode::reverse:
          pb_val = map(cur_exp_val,heel_val_,toes_val_,16383,0);
          break;
      }
      pb_val = constrain(pb_val,0,16383);
      uint8_t pb_val_lsb = 0x7F & pb_val;
      uint8_t pb_val_msb = 0x7F & (pb_val >> 7);
      midi_send_cvm(status,pb_val_lsb,pb_val_msb);
}

//void ExpPedal::process_pb(int16_t cur_exp_val){}

void ExpPedal::process()
{
  raw_exp_val_= analogRead(exp_pin_);
  unsigned long cur_millis = millis();

//  Serial.print(" exp val : ");
//  Serial.print(raw_exp_val_, DEC);
//  Serial.print("\r\n");
//  if (old_exp_val_ != raw_exp_val_)
  if ((cur_millis - change_delay_millis_) > changeDelayTime_)
  {
    int16_t diff = abs(raw_exp_val_ - old_exp_val_);
    if (diff > dead_zone_)
    {
      change_delay_millis_ = cur_millis;
      switch(cmd_typ_)
      {
        case expCmdTyp_t::cc:
          process_cc(raw_exp_val_);
          break;
        case expCmdTyp_t::pitch_bend:
          process_pb(raw_exp_val_);
          break;
        default:
          break;
      }
      old_exp_val_ = raw_exp_val_;
    }
  }
}

