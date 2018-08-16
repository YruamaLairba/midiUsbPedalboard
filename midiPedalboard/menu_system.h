#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "setup.h"
#include "rotary_encoder.h"
#include "push_button.h"
#include "warnings.h"
#include "display.h"

DIAGNOSTIC_IGNORE_ALL
#ifdef DEBUG
#include <Arduino.h>
#endif //DEBUG

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
DIAGNOSTIC_POP

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

class MenuBase;
class MenuConf;
class MenuSystem;

class MenuBase
{
  protected:
    MenuSystem* pt_menu_system_;
  public:
    MenuBase(MenuSystem* pt_menu_system);
    virtual void select_next() = 0;
    virtual void select_prev() = 0;
    virtual void validate() = 0;
    virtual void cancel() = 0;
    virtual void print() = 0;
};

class MenuTemplate : public MenuBase
{
  protected:
    uint8_t selection_;
    uint8_t selection_max_;
    uint8_t display_offset_;
    virtual void reset();
  public:
    MenuTemplate(MenuSystem* menu_system);
    virtual void select_next();
    virtual void select_prev();
};

// for menus with a parent
class SubMenuTemplate : public MenuTemplate
{
  protected:
    MenuBase* pt_parent_;
  public:
    SubMenuTemplate(MenuSystem* pt_menu_system, MenuBase* pt_parent);
    virtual void activate();
    virtual void cancel();
};

class MenuControllerSetting : public SubMenuTemplate
{
  public:
    MenuControllerSetting(MenuSystem* menu_system, MenuBase* pt_parent);
    virtual void validate();
    virtual void print();
};

class MenuPresetLoad : public SubMenuTemplate
{
  public:
    MenuPresetLoad(MenuSystem* menu_system, MenuBase* pt_parent);
    virtual void validate();
    virtual void print();
};


class MenuConf : public MenuTemplate
{
  public:
    MenuConf(MenuSystem* menu_system);
    MenuControllerSetting menu_controller_setting_;
    MenuPresetLoad menu_preset_load_;
    virtual void validate();
    virtual void cancel();
    virtual void print();
};

class MenuSystem
{
  private:
    MenuConf root_;
    MenuBase* pt_current_;
    RotaryEncoder rotary_encoder_;
    PushButton button_ok_;
    PushButton button_cancel_;

  public:
    MenuSystem();
    void init();
    void set_active(MenuBase* activated);
    void process();
};


#endif //MENU_SYSTEM_H
