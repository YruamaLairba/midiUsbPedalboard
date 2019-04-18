#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include <stdint.h>
#include "warnings.h"
DIAGNOSTIC_IGNORE_ALL
#include <Arduino.h>
DIAGNOSTIC_POP

//#warning "fix me"
typedef uint8_t fsCommand_t;

typedef enum class fsCmdTyp: uint8_t
{
  cc, MIN=cc,
  pgm, MAX=pgm
} fsCmdTyp_t;

struct fsMode
{
  enum 
  {
    toggle_off, MIN = toggle_off, //mode toggle, switch is off
    toggle_on, //mode toggle, switch is on
    momentary_off, //mode momentarily off, normally on
    momentary_on, //mode momentarily on, normally off
    single_off, //only a "off" message
    single_on,MAX = single_on, //only a "on" message
    nb_item
  };
};

//this structure is used to store fs data in eeprom
struct FsConfig
{
  uint8_t command:7,:1;
  uint8_t mode:4;
  uint8_t cmd_typ:4;
};

class ControllerSystem;
class Footswitch
{
  private:
    static const unsigned long debounceTime_ = 100;
    static const unsigned long ledTime_ = 100;
    fsCmdTyp_t cmd_typ_;
    uint8_t command_;
    uint8_t mode_;

    uint8_t fs_pin_; //input pin
    uint8_t led_pin_; //output pin for the led

    uint8_t old_fs_pin_val_; //HIGH or LOW

    uint8_t fs_val_;//virtual value of the pin
    unsigned long led_millis_;//used to make led flash or blink
    unsigned long debounce_millis_;//for debouncing

    ControllerSystem* pt_controller_system_;
    void midi_send(uint8_t val);

  public:
    Footswitch();
    void setup(uint8_t fs_pin, uint8_t led_pin,
      ControllerSystem* pt_controller_system_);

    fsCmdTyp_t get_cmd_typ();
    void set_cmd_typ(fsCmdTyp cmd_typ);

    uint8_t get_command();
    void set_command(uint8_t command);

    uint8_t get_mode();
    void set_mode(uint8_t mode);

    FsConfig get_config();
    void set_config(FsConfig conf);

    void process();
};



#endif //FOOTSWITCH_H
