#include "menu_system.h"

MenuSystem::MenuBase::MenuBase(MenuSystem* pt_menu_system)
  : pt_menu_system_(pt_menu_system)
{}

MenuSystem::MenuTemplate::MenuTemplate(MenuSystem* pt_menu_system)
  : MenuBase(pt_menu_system)
  , selection_(0)
  , display_offset_(0)
{}

void MenuSystem::MenuTemplate::reset()
{
  selection_ = 0;
  display_offset_ = 0;
}

void MenuSystem::MenuTemplate::select_next()
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

void MenuSystem::MenuTemplate::select_prev()
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

MenuSystem::SubMenuTemplate::SubMenuTemplate(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent)
  : MenuTemplate(pt_menu_system)
  , pt_parent_(pt_parent)
{}

void MenuSystem::SubMenuTemplate::activate()
{
  pt_menu_system_->set_active(this);
}

void MenuSystem::SubMenuTemplate::cancel()
{
  pt_menu_system_->set_active(pt_parent_);
}

MenuSystem::MenuFsCommand::MenuFsCommand(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsCommand::get_nb_item(){return 128;}

void MenuSystem::MenuFsCommand::validate(){}

void MenuSystem::MenuFsCommand::print()
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

MenuSystem::MenuFsMode::MenuFsMode(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsMode::get_nb_item(){return fsMode::nb_item;}

void MenuSystem::MenuFsMode::validate(){}

void MenuSystem::MenuFsMode::print()
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

MenuSystem::MenuExpCommand::MenuExpCommand(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpCommand::get_nb_item(){return 128;}

void MenuSystem::MenuExpCommand::validate(){}

void MenuSystem::MenuExpCommand::print()
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

MenuSystem::MenuExpMode::MenuExpMode(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpMode::get_nb_item(){return expMode::nb_item;}

void MenuSystem::MenuExpMode::validate(){}

void MenuSystem::MenuExpMode::print()
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

MenuSystem::MenuFsSetting::MenuFsSetting(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_fs_command_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_fs_mode_(pt_menu_system, this, pt_menu_controller_setting)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsSetting::get_nb_item(){return 2;}

void MenuSystem::MenuFsSetting::validate()
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

void MenuSystem::MenuFsSetting::print()
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

MenuSystem::MenuExpSetting::MenuExpSetting(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_exp_command_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_exp_mode_(pt_menu_system, this, pt_menu_controller_setting)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpSetting::get_nb_item(){return 2;}

void MenuSystem::MenuExpSetting::validate()
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


void MenuSystem::MenuExpSetting::print()
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

MenuSystem::MenuControllerSetting::MenuControllerSetting(
    MenuSystem* pt_menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_fs_setting_(pt_menu_system,this,this)
  , menu_exp_setting_(pt_menu_system,this,this)
{}

uint8_t MenuSystem::MenuControllerSetting::get_nb_item()
{
  return pt_menu_system_->pt_controller_system_->get_nb_fs() +
    pt_menu_system_->pt_controller_system_->get_nb_exp() ;
}

void MenuSystem::MenuControllerSetting::validate()
{
  uint8_t nb_fs = pt_menu_system_->pt_controller_system_->get_nb_fs();
  uint8_t nb_exp = pt_menu_system_->pt_controller_system_->get_nb_exp();
  if(selection_ < nb_fs)
  {
    menu_fs_setting_.activate();
  }
  else if (selection_ >= nb_fs && selection_ < nb_fs + nb_exp)
  {
    menu_exp_setting_.activate();
  }
}

void MenuSystem::MenuControllerSetting::print()
{
  uint8_t nb_fs = pt_menu_system_->pt_controller_system_->get_nb_fs();
  uint8_t nb_exp = pt_menu_system_->pt_controller_system_->get_nb_exp();
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
    if (i < nb_fs)
    {
      display.print(F("FS "));
      display.print(i, DEC);
    }
    else if (i < (nb_fs + nb_exp))
    {
      display.print(F("Exp "));
      display.print(i - nb_fs, DEC);
    }
    display.print(F("\n\r"));
  }
  display.display();
}

uint8_t MenuSystem::MenuControllerSetting::get_selected_fs()
{
  return selection_;
}

uint8_t MenuSystem::MenuControllerSetting::get_selected_exp()
{
  return selection_ -
    pt_menu_system_->pt_controller_system_->get_nb_fs();
}

MenuSystem::MenuPresetLoad::MenuPresetLoad(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuSystem::MenuPresetLoad::get_nb_item(){return 2;}

void MenuSystem::MenuPresetLoad::validate(){}

void MenuSystem::MenuPresetLoad::print()
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

MenuSystem::MenuPresetSave::MenuPresetSave(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuSystem::MenuPresetSave::get_nb_item(){return 111;}

void MenuSystem::MenuPresetSave::validate(){}

void MenuSystem::MenuPresetSave::print()
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

MenuSystem::MenuMidiChannel::MenuMidiChannel(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuSystem::MenuMidiChannel::get_nb_item(){return 16;}

void MenuSystem::MenuMidiChannel::validate(){}

void MenuSystem::MenuMidiChannel::print()
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
    display.print(F("Channel "));
    display.print(i + 1);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuGlobalSetting::MenuGlobalSetting(
    MenuSystem* pt_menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_midi_channel_(pt_menu_system, this)
{}

uint8_t MenuSystem::MenuGlobalSetting::get_nb_item(){return 2;}

void MenuSystem::MenuGlobalSetting::validate()
{
  switch(selection_)
  {
    case 0:
      menu_midi_channel_.activate();
      break;
  }
}

void MenuSystem::MenuGlobalSetting::print()
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

MenuSystem::MenuConf::MenuConf(MenuSystem* menu_system)
  : MenuTemplate(menu_system)
  , menu_controller_setting_(menu_system,this)
  , menu_preset_load_(menu_system,this)
  , menu_preset_save_(menu_system,this)
  , menu_global_setting_(menu_system,this)
{}

uint8_t MenuSystem::MenuConf::get_nb_item(){return 4;}

void MenuSystem::MenuConf::validate()
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

void MenuSystem::MenuConf::cancel()
{
}

void MenuSystem::MenuConf::print()
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

MenuSystem::MenuSystem(ControllerSystem* pt_controller_system)
  : root_(this)
  , pt_current_(&root_)
  , rotary_encoder_(rotaryPinA,rotaryPinB)
  , button_ok_(buttonOkPin)
  , button_cancel_(buttonCancelPin)
  , pt_controller_system_(pt_controller_system)
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

