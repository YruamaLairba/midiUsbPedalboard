#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include <stdint.h>
#include <Arduino.h>

//#warning "fix me"
typedef uint8_t fsCommand_t;

struct fsMode
{
  enum 
  {
    toggle_off, MIN = toggle_off, //mode toggle, switch is off
    toggle_on, //mode toggle, switch is on
    momentary_off, //mode momentarily off, normally on
    momentary_on, //mode momentarily on, normally off
    single_off, //only a "off" message
    single_on,MAX = single_on //only a "on" message
  };
};

struct FsConfig
{
  uint8_t command;
  uint8_t mode;
};

class Footswitch
{
  private:
    static const unsigned long debounceTime_ = 100;
    static const unsigned long ledTime_ = 100;
    uint8_t command_;
    uint8_t mode_;

    uint8_t fs_pin_; //input pin
    uint8_t led_pin_; //output pin for the led

    uint8_t old_fs_pin_val_; //HIGH or LOW

    uint8_t fs_val_;//virtual value of the pin
    unsigned long led_millis_;//used to make led flash or blink
    unsigned long debounce_millis_;//for debouncing

  public:
    Footswitch();
    void setup(uint8_t fs_pin, uint8_t led_pin);
    uint8_t get_command() {return command_;};
    void set_command(uint8_t command);

    uint8_t get_mode(){return mode_;};
    void set_mode(uint8_t mode);

    FsConfig get_config();
    void set_config(FsConfig conf);

    //void set_mode(uint8_t mode){mode_ = mode;};

    //return 127 when fs change to on
    //return 0 when fs change to off
    //return -1 when fs state doesn't change
    int8_t read();
};



#endif //FOOTSWITCH_H
