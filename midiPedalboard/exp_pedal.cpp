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

void ExpPedal::reset()
{
  cmd_typ_ = expCmdTyp_t::none;
  command_ = 0;
  mode_ = 0;
}

void ExpPedal::process_cc(int16_t cur_exp_val)
{
  uint8_t status = 0xB0|pt_controller_system_->get_midi_channel();
  uint8_t cc_val;
      switch(mode_)
      {
        case expMode::normal:
          cc_val = cur_exp_val/8;
          break;
        case expMode::reverse:
          cc_val = (1023-cur_exp_val)/8;
          break;
      }
      midi_send_cvm(status,get_command(),cc_val);
}

//void ExpPedal::process_pb(int16_t cur_exp_val){}

void ExpPedal::process()
{
  int16_t cur_exp_val= analogRead(exp_pin_);
  unsigned long cur_millis = millis();

//  Serial.print(" exp val : ");
//  Serial.print(cur_exp_val, DEC);
//  Serial.print("\r\n");
//  if (old_exp_val_ != cur_exp_val)
  if ((cur_millis - change_delay_millis_) > changeDelayTime_)
  {
    int16_t diff = abs(cur_exp_val - old_exp_val_);
    if (diff > dead_zone_)
    {
      change_delay_millis_ = cur_millis;
      switch(cmd_typ_)
      {
        case expCmdTyp_t::cc:
          process_cc(cur_exp_val);
          break;
        case expCmdTyp_t::pitch_bend:
          break;
        default:
          break;
      }
      old_exp_val_ = cur_exp_val;
    }
  }
}

