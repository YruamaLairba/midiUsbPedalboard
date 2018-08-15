#include "menu_system.h"

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

void MenuSystem::set_active(AbstractMenu* activated)
{
  pt_current_ = activated;
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
  }
  if(button_cancel_.read()== PushButtonVal::pressed)
  {
  }
}

MenuBase::MenuBase(MenuSystem* menu_system)
  : menu_system_(menu_system)
  , selection_(0)
  , display_offset_(0)
{}

void MenuBase::reset()
{
  selection_ = 0;
  display_offset_ = 0;
}

void MenuBase::select_next()
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

void MenuBase::select_prev()
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

MenuConf::MenuConf(MenuSystem* menu_system)
  : MenuBase(menu_system)
{
  selection_max_ = 3;
}

void MenuConf::validate()
{
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
        display.print(F("SW set"));
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
