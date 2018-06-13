#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include <stdint.h>

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

class footswitch
{
  private:
    uint8_t command;
    uint8_t mode;
  
  public:
    uint8_t get_command() {return command;};
    void set_command(uint8_t command){this->command = command;};

    uint8_t get_mode(){return mode;};
    void set_mode(uint8_t mode){this->mode = mode;};  
};



#endif //FOOTSWITCH_H
