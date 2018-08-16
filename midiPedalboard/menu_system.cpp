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
  if (selection_ < selection_max_)
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

SubMenuTemplate::SubMenuTemplate(MenuSystem* pt_menu_system, MenuBase* pt_parent)
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

MenuControllerSetting::MenuControllerSetting(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{
  selection_max_ = nbFs + nbExp - 1;
}

void MenuControllerSetting::validate(){}

void MenuControllerSetting::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i <= selection_max_ && i < (display_offset_ + 4); i++)
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

MenuPresetLoad::MenuPresetLoad(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{
  selection_max_ = 2;
}

void MenuPresetLoad::validate(){}

void MenuPresetLoad::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i <= selection_max_ && i < display_offset_ + 4; i++)
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

MenuConf::MenuConf(MenuSystem* menu_system)
  : MenuTemplate(menu_system)
  , menu_controller_setting_(menu_system,this)
  , menu_preset_load_(menu_system,this)
{
  selection_max_ = 3;
}

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
  }
}

void MenuConf::cancel()
{
}

void MenuConf::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_; i< (display_offset_ + 4); i++)
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

