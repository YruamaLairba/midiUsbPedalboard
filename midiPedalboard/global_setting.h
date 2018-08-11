#ifndef GLOBAL_SETTING_H
#define GLOBAL_SETTING_H

#include "setup.h"
#include "eeprom_config.h"
#include "warnings.h"

#include <stdint.h>
DIAGNOSTIC_IGNORE_ALL
#include <EEPROM.h>
DIAGNOSTIC_POP

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

