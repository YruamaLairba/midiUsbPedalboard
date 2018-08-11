#include "global_setting.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <EEPROM.h>
DIAGNOSTIC_POP

void GlobalSetting::init()
{
  EEPROM.get(eeprom_midi_channel_start,midi_channel_);
  if (midi_channel_ > 15) midi_channel_ = 0;
}



void GlobalSetting::set_midi_channel(uint8_t midi_channel)
{
  midi_channel_=midi_channel;
  if (midi_channel_ > 15) midi_channel_ = 0;
  EEPROM.put(eeprom_midi_channel_start,midi_channel);
}


