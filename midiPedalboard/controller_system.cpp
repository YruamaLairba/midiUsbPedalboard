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


