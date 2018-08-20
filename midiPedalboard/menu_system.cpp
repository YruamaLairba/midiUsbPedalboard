#include "menu_system.h"

MenuBase::MenuBase(MenuSystem* pt_menu_system)
  : pt_menu_system_(pt_menu_system)
{}

MenuTemplate::MenuTemplate(MenuSystem* pt_menu_system)
  : MenuBase(pt_menu_system)
  , selection_(0)
  , display_offset_(0)
{}

void MenuTemplate::reset()
{
  selection_ = 0;
  display_offset_ = 0;
}

void MenuTemplate::select_next()
{
  if (selection_ < get_nb_item()-1)
  {
    selection_++;
  }
  if (selection_ >= (display_offset_ + 4 ))
  {
    display_offset_++;
  }
  print();
}

void MenuTemplate::select_prev()
{
  if (selection_ > 0)
  {
    selection_--;
  }
  if (selection_ < display_offset_)
  {
    display_offset_--;
  }
  print();
}

SubMenuTemplate::SubMenuTemplate(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent)
  : MenuTemplate(pt_menu_system)
  , pt_parent_(pt_parent)
{}

void SubMenuTemplate::activate()
{
  pt_menu_system_->set_active(this);
}

void SubMenuTemplate::cancel()
{
  pt_menu_system_->set_active(pt_parent_);
}

MenuFsCommand::MenuFsCommand(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuFsCommand::get_nb_item(){return 128;}

void MenuFsCommand::validate(){}

void MenuFsCommand::print()
{
  uint8_t fsNum = pt_menu_controller_setting_->get_selected_fs();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("CC"));
    display.print(i, DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuFsMode::MenuFsMode(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuFsMode::get_nb_item(){return fsMode::nb_item;}

void MenuFsMode::validate(){}

void MenuFsMode::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = display_offset_; i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
  switch (i)
    {
      case fsMode::toggle_off:
        display.print(F("tog off"));
        break;
      case fsMode::toggle_on:
        display.print(F("tog on"));
        break;
      case fsMode::momentary_off:
        display.print(F("mom (off)"));
        break;
      case fsMode::momentary_on:
        display.print(F("mom (on)"));
        break;
      case fsMode::single_off:
        display.print(F("sing off"));
        break;
      case fsMode::single_on:
        display.print(F("sing on"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuExpCommand::MenuExpCommand(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuExpCommand::get_nb_item(){return 128;}

void MenuExpCommand::validate(){}

void MenuExpCommand::print()
{
  uint8_t fsNum = pt_menu_controller_setting_->get_selected_fs();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("CC"));
    display.print(i, DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuExpMode::MenuExpMode(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuExpMode::get_nb_item(){return expMode::nb_item;}

void MenuExpMode::validate(){}

void MenuExpMode::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = display_offset_; i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
  switch (i)
    {
      case expMode::normal:
        display.print(F("normal"));
        break;
      case expMode::reverse:
        display.print(F("reverse"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuFsSetting::MenuFsSetting(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_fs_command_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_fs_mode_(pt_menu_system, this, pt_menu_controller_setting)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuFsSetting::get_nb_item(){return 2;}

void MenuFsSetting::validate()
{
  switch(selection_)
  {
    case 0:
      menu_fs_command_.activate();
      break;
    case 1:
      menu_fs_mode_.activate();
      break;
  }
}

void MenuFsSetting::print()
{
  uint8_t fsNum = pt_menu_controller_setting_->get_selected_fs();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("FS"));
    display.print(fsNum, DEC);
    switch (i)
    {
      case 0:
        display.print(F(" Cmd"));
        break;
      case 1:
        display.print(F(" Mode"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuExpSetting::MenuExpSetting(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_exp_command_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_exp_mode_(pt_menu_system, this, pt_menu_controller_setting)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuExpSetting::get_nb_item(){return 2;}

void MenuExpSetting::validate()
{
  switch(selection_)
  {
    case 0:
      menu_exp_command_.activate();
      break;
    case 1:
      menu_exp_mode_.activate();
      break;
  }
}


void MenuExpSetting::print()
{
  uint8_t expNum = pt_menu_controller_setting_->get_selected_exp();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Exp"));
    display.print(expNum, DEC);
    switch (i)
    {
      case 0:
        display.print(F(" Cmd"));
        break;
      case 1:
        display.print(F(" Mode"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuControllerSetting::MenuControllerSetting(
    MenuSystem* pt_menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_fs_setting_(pt_menu_system,this,this)
  , menu_exp_setting_(pt_menu_system,this,this)
{}

uint8_t MenuControllerSetting::get_nb_item(){return nbFs + nbExp;}

void MenuControllerSetting::validate()
{
  if(selection_ < nbFs)
  {
    menu_fs_setting_.activate();
  }
  else if (selection_ >= nbFs && selection_ < nbFs + nbExp)
  {
    menu_exp_setting_.activate();
  }
}

void MenuControllerSetting::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    if (i < nbFs)
    {
      display.print(F("FS "));
      display.print(i, DEC);
    }
    else if (i < (nbFs + nbExp))
    {
      display.print(F("Exp "));
      display.print(i - nbFs, DEC);
    }
    display.print(F("\n\r"));
  }
  display.display();
}

uint8_t MenuControllerSetting::get_selected_fs()
{
  return selection_;
}

uint8_t MenuControllerSetting::get_selected_exp()
{
  return selection_ - nbFs;
}

MenuPresetLoad::MenuPresetLoad(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuPresetLoad::get_nb_item(){return 2;}

void MenuPresetLoad::validate(){}

void MenuPresetLoad::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Load "));
    display.print(i,DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuPresetSave::MenuPresetSave(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuPresetSave::get_nb_item(){return 111;}

void MenuPresetSave::validate(){}

void MenuPresetSave::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Save to "));
    display.print(i,DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuGlobalSetting::MenuGlobalSetting(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuGlobalSetting::get_nb_item(){return 2;}

void MenuGlobalSetting::validate(){}

void MenuGlobalSetting::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    switch(i)
    {
      case 0:
        display.print(F("Midi chan"));
        break;
      case 1:
        display.print(F("Exp cal"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuConf::MenuConf(MenuSystem* menu_system)
  : MenuTemplate(menu_system)
  , menu_controller_setting_(menu_system,this)
  , menu_preset_load_(menu_system,this)
  , menu_preset_save_(menu_system,this)
  , menu_global_setting_(menu_system,this)
{}

uint8_t MenuConf::get_nb_item(){return 4;}

void MenuConf::validate()
{
  switch(selection_)
  {
    case 0:
      menu_controller_setting_.activate();
      break;
    case 1:
      menu_preset_load_.activate();
      break;
    case 2:
      menu_preset_save_.activate();
      break;
    case 3:
      menu_global_setting_.activate();
      break;
  }
}

void MenuConf::cancel()
{
}

void MenuConf::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
      {
        display.setTextColor(BLACK,WHITE);
      }
      else
      {
        display.setTextColor(WHITE,BLACK);
      }
      switch(i)
    {
      case 0:
        display.print(F("Cont. set"));
        break;
      case 1:
        display.print(F("Load Pres"));
        break;
      case 2:
        display.print(F("Save Pres"));
        break;
      case 3:
        display.print(F("Gen. set"));
        break;
      default:
        break;
    }
   display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuSystem()
  : root_(this)
  , pt_current_(&root_)
  , rotary_encoder_(rotaryPinA,rotaryPinB)
  , button_ok_(buttonOkPin)
  , button_cancel_(buttonCancelPin)
{

}

void MenuSystem::init()
{
}

void MenuSystem::set_active(MenuBase* activated)
{
  pt_current_ = activated;
  pt_current_->print();
}

void MenuSystem::process()
{
  switch(rotary_encoder_.read())
  {
    case 1:
      pt_current_->select_next();
      break;
    case -1:
      pt_current_->select_prev();
      break;
  }
  if(button_ok_.read()== PushButtonVal::pressed)
  {
    pt_current_->validate();
  }
  if(button_cancel_.read()== PushButtonVal::pressed)
  {
    pt_current_->cancel();
  }
}

