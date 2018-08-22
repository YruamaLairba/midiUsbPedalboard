#include "controller_system.h"

ControllerSystem::ControllerSystem()
  : preset_(fs_tab_, nb_fs_, exp_tab_, nb_exp_)
{}

void ControllerSystem::init()
{
  global_setting_.init();
  for (uint8_t i = 0; i < nb_fs_; i++)
  {
    fs_tab_[i].setup(fsPins[i], fsLedPins[i], &global_setting_);
  }
  for(uint8_t i=0; i<nb_exp_; i++)
  {
    exp_tab_[i].setup(expPins[i], &global_setting_);
  }
  preset_.init();
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

uint8_t ControllerSystem::get_fs_command(uint8_t fs_num)
{
  return fs_tab_[fs_num].get_command();
}

void ControllerSystem::set_fs_command(uint8_t fs_num, uint8_t fs_cmd)
{
  fs_tab_[fs_num].set_command(fs_cmd);
}

uint8_t ControllerSystem::get_fs_mode(uint8_t fs_num)
{
  return fs_tab_[fs_num].get_mode();
}

void ControllerSystem::set_fs_mode(uint8_t fs_num, uint8_t fs_mode)
{
  fs_tab_[fs_num].set_mode(fs_mode);
}

uint8_t ControllerSystem::get_exp_command(uint8_t exp_num)
{
  return exp_tab_[exp_num].get_command();
}

void ControllerSystem::set_exp_command(uint8_t exp_num, uint8_t exp_cmd)
{
  exp_tab_[exp_num].set_command(exp_cmd);
}

uint8_t ControllerSystem::get_exp_mode(uint8_t exp_num)
{
  return exp_tab_[exp_num].get_mode();
}

void ControllerSystem::set_exp_mode(uint8_t exp_num, uint8_t exp_mode)
{
  exp_tab_[exp_num].set_mode(exp_mode);
}

