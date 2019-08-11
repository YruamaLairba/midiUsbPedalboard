#ifndef EXP_PEDAL_H
#define EXP_PEDAL_H

#include <stdint.h>
#include "warnings.h"
DIAGNOSTIC_IGNORE_ALL
#include <Arduino.h>
DIAGNOSTIC_POP

//#warning "fix me"
typedef uint8_t expCommand_t;

enum class expCmdTyp_t: uint8_t
{
  none, MIN=none,
  cc,
  pitch_bend, MAX=pitch_bend
} ;


struct expMode
{
  enum 
  {
    normal, MIN = normal, //mode toggle, switch is off
    reverse, MAX = reverse, //only a "on" message
    nb_item
  };
};

struct ExpConfig
{
  uint8_t command:7,:1;
  uint8_t mode:4;
  uint8_t cmd_typ:4;
};

class ControllerSystem;
class ExpPedal
{
  private:
    static const unsigned long changeDelayTime_ = 0;
    static const int16_t dead_zone_ = 8;

    expCmdTyp_t cmd_typ_;
    uint8_t command_;
    uint8_t mode_;

    uint8_t exp_pin_; //analog input pin

    int16_t raw_exp_val_; //raw value value from last adc read
    int16_t old_exp_val_; //used to filter noise on the raw value
    uint16_t exp_val_;//virtual value of the pin

    unsigned long change_delay_millis_;//for debouncing

    ControllerSystem* pt_controller_system_;
    void midi_send(uint8_t val);
    void process_cc(int16_t cur_exp_val);
    void process_pb(int16_t cur_exp_val);//pitch_bend

  public:
    ExpPedal();
    void setup(uint8_t exp_pin, ControllerSystem* pt_controller_system);
    uint8_t get_command() {return command_;};
    void set_command(uint8_t command);

    expCmdTyp_t get_cmd_typ(){return cmd_typ_;};
    void set_cmd_typ(expCmdTyp_t cmd_typ);

    uint8_t get_mode(){return mode_;};
    void set_mode(uint8_t mode);

    ExpConfig get_config();
    void set_config(ExpConfig conf);

    //get raw value of the exp pedal,
    int16_t get_raw_val();//void set_mode(uint8_t mode){mode_ = mode;};

    //return value when positive
    //return -1 when fs state doesn't change
    void reset();

    void process();
};



#endif //EXP_PEDAL_H

