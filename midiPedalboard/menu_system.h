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

class AbstractMenu;
class MenuConf;
class MenuSystem;

class AbstractMenu
{
  public:
    virtual void select_next() = 0;
    virtual void select_prev() = 0;
    virtual void validate() = 0;
    virtual void cancel() = 0;
    virtual void print() = 0;
};

class MenuBase : public AbstractMenu
{
  protected:
    MenuSystem* menu_system_;
    uint8_t selection_;
    uint8_t selection_max_;
    uint8_t display_offset_;
    virtual void reset();
  public:
    MenuBase(MenuSystem* menu_system);
    virtual void select_next();
    virtual void select_prev();
    virtual void validate() = 0;
    virtual void cancel() = 0;
    virtual void print() = 0;
};

class MenuConf : public MenuBase
{
  public:
    MenuConf(MenuSystem* menu_system);
    virtual void validate();
    virtual void cancel();
    virtual void print();
};

class MenuSystem
{
  private:
    MenuConf root_;
    AbstractMenu* pt_current_;
    RotaryEncoder rotary_encoder_;
    PushButton button_ok_;
    PushButton button_cancel_;

  public:
    MenuSystem();
    void init();
    void set_active(AbstractMenu* activated);
    void process();
};


#endif //MENU_SYSTEM_H
