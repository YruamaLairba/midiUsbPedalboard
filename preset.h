#ifndef PRESET_H
#define PRESET_H

#include <stdint.h>
#include "footswitch.h"



class Preset
{
  private:
    footswitch* footswitches;
    uint8_t nbFootswitches;
    
  public:
    Preset(footswitch* footswitches, uint8_t nbFootswitches):
    footswitches(footswitches),
    nbFootswitches(nbFootswitches)
    {}

    //save(int8_t presetNumber);
    //load(int8_t presetNumber);

    footswitch* get_fs(uint8_t);
    
};





#endif //PRESET_H
