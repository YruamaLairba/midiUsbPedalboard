#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include <stdint.h>

//#warning "fix me"
typedef uint8_t fsCommand_t;

struct fsMode
{
  enum 
  {
    toggle_on, MIN = toggle_on,
    toggle_off,
    momentary_on,
    momentary_off,
    single_on,
    single_off,MAX = single_off
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
