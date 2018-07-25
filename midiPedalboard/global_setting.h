#ifndef GLOBAL_SETTING_H
#define GLOBAL_SETTING_H

#include <stdint.h>
#include "setup.h"
#include "EEPROM.h"
#include "eeprom_config.h"

#warning "TODO: eeprom save and load"
class GlobalSetting
{
  private:
    uint8_t midi_channel_;

  public:
    GlobalSetting() : midi_channel_(0){};

    void init();
    void set_midi_channel(uint8_t midi_channel);
    uint8_t get_midi_channel(){return midi_channel_;};
};




#endif //GLOBAL_SETTING_H
