#include "global_setting.h"

void GlobalSetting::init()
{
  EEPROM.get(eeprom_midi_channel_start,midi_channel_);
}

void GlobalSetting::set_midi_channel(uint8_t midi_channel)
{
  midi_channel_=midi_channel;
  EEPROM.put(eeprom_midi_channel_start,midi_channel);
}


