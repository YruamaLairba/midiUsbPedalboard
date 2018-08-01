#ifndef EXP_PEDAL_H
#define EXP_PEDAL_H

#include <stdint.h>
#include <Arduino.h>

//#warning "fix me"
typedef uint8_t expCommand_t;

struct expMode
{
  enum 
  {
    normal, MIN = normal, //mode toggle, switch is off
    reverse, MAX = reverse //only a "on" message
  };
};

struct ExpConfig
{
  uint8_t command;
  uint8_t mode;
};

class ExpPedal
{
  private:
    static const unsigned long changeDelayTime_ = 100;
    static const int16_t dead_zone_ = 8;

    uint8_t command_;
    uint8_t mode_;

    uint8_t exp_pin_; //analog input pin

    int16_t old_exp_val_; //
    uint16_t exp_val_;//virtual value of the pin

    unsigned long change_delay_millis_;//for debouncing

  public:
    ExpPedal();
    void setup(uint8_t exp_pin);
    uint8_t get_command() {return command_;};
    void set_command(uint8_t command);

    uint8_t get_mode(){return mode_;};
    void set_mode(uint8_t mode);

    ExpConfig get_config();
    void set_config(ExpConfig conf);

    //void set_mode(uint8_t mode){mode_ = mode;};

    //return value when positive
    //return -1 when fs state doesn't change
    int16_t read();
};



#endif //EXP_PEDAL_H

