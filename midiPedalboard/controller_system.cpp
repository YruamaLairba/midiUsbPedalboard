#include "controller_system.h"
#include "warnings.h"
DIAGNOSTIC_IGNORE_ALL
#include <EEPROM.h>
DIAGNOSTIC_POP


ControllerSystem::ControllerSystem()
{}

void ControllerSystem::init()
{
  //load midi channel
  EEPROM.get(eeprom_midi_channel_start,midi_channel_);
  if (midi_channel_ > 15) midi_channel_ = 0;
  //initialize controller
  for (uint8_t i = 0; i < nb_fs_; i++)
  {
    fs_tab_[i].setup(fsPins[i], fsLedPins[i], this);
  }
  for(uint8_t i=0; i<nb_exp_; i++)
  {
    exp_tab_[i].setup(expPins[i], this);
  }
  //initialize preset
  EEPROM.get(eeprom_preset_number_start, current_preset_);
  load_preset(current_preset_);
}

void ControllerSystem::process()
{
  for (uint8_t i = 0; i < nb_fs_; i++)
  {
    fs_tab_[i].process();
  }
  for(uint8_t i = 0; i<nb_exp_; i++)
  {
    exp_tab_[i].process();
  }
}

fsCmdTyp_t ControllerSystem::get_fs_cmd_typ(uint8_t fs_num)
{
  return fs_tab_[fs_num].get_cmd_typ();
}

void ControllerSystem::set_fs_cmd_typ(uint8_t fs_num, fsCmdTyp_t fs_cmd_typ)
{
  fs_tab_[fs_num].set_cmd_typ(fs_cmd_typ);
  is_preset_modified_ = true;
}

uint8_t ControllerSystem::get_fs_command(uint8_t fs_num)
{
  return fs_tab_[fs_num].get_command();
}

void ControllerSystem::set_fs_command(uint8_t fs_num, uint8_t fs_cmd)
{
  fs_tab_[fs_num].set_command(fs_cmd);
  is_preset_modified_ = true;
}

uint8_t ControllerSystem::get_fs_mode(uint8_t fs_num)
{
  return fs_tab_[fs_num].get_mode();
}

void ControllerSystem::set_fs_mode(uint8_t fs_num, uint8_t fs_mode)
{
  fs_tab_[fs_num].set_mode(fs_mode);
  is_preset_modified_ = true;
}

uint8_t ControllerSystem::get_exp_command(uint8_t exp_num)
{
  return exp_tab_[exp_num].get_command();
}

void ControllerSystem::set_exp_command(uint8_t exp_num, uint8_t exp_cmd)
{
  exp_tab_[exp_num].set_command(exp_cmd);
  is_preset_modified_ = true;
}

uint8_t ControllerSystem::get_exp_mode(uint8_t exp_num)
{
  return exp_tab_[exp_num].get_mode();
}

void ControllerSystem::set_exp_mode(uint8_t exp_num, uint8_t exp_mode)
{
  exp_tab_[exp_num].set_mode(exp_mode);
  is_preset_modified_ = true;
}

uint8_t ControllerSystem::get_nb_preset()
{
  return nb_preset_;
}

uint8_t ControllerSystem::get_current_preset()
{
  return current_preset_;
}

bool ControllerSystem::is_preset_modified()
{
  return is_preset_modified_;
}

void ControllerSystem::load_preset(uint8_t preset_num)
{
  if (preset_num < nb_preset_)
  {
    current_preset_ = preset_num;
    PresetData data;
    EEPROM.put(eeprom_preset_number_start, current_preset_);
    //note : preset are stored in reverse order in the eeprom
    EEPROM.get(int(eeprom_preset_bank_end + 1U -
        (current_preset_ + 1U) * sizeof(data)),data);
    //fs
    for(uint8_t i=0; i< nb_fs_; i++)
    {
      fs_tab_[i].set_config(data.fsConfigs[i]);
    }
    //exp pedal
    for(uint8_t i=0; i< nb_exp_; i++)
    {
      exp_tab_[i].set_config(data.expConfigs[i]);
    }
    is_preset_modified_ = false;
  }
}

void ControllerSystem::save_preset(uint8_t preset_num)
{
  if(preset_num < nb_preset_)
  {
    current_preset_ = preset_num;
    PresetData data;
    //fs
    for(uint8_t i=0; i< min(nb_fs_,nbFs); i++)
    {
      data.fsConfigs[i] = fs_tab_[i].get_config();
    }
    //exp pedal
    for(uint8_t i=0; i< min(nb_exp_,nbExp); i++)
    {
      data.expConfigs[i] = exp_tab_[i].get_config();
    }
    //note : preset are stored in reverse order in the eeprom
    EEPROM.put(int(eeprom_preset_bank_end + 1U -
        (current_preset_ + 1U) * sizeof(data)),data);
    EEPROM.put(eeprom_preset_number_start, current_preset_);
    is_preset_modified_ = false;
  }
}

uint8_t ControllerSystem::get_midi_channel()
{
  return midi_channel_;
}

void ControllerSystem::set_midi_channel(uint8_t channel)
{
  midi_channel_=channel;
  if (midi_channel_ > 15) midi_channel_ = 0;
  EEPROM.put(eeprom_midi_channel_start,midi_channel_);
}
