#include "preset.h"

#ifdef DEBUG
#include <Arduino.h>
#endif //DEBUG

//ctor
Preset::Preset(){}

Preset::Preset(Footswitch* fs_tab, uint8_t nb_fs,
    ExpPedal* exp_tab, uint8_t nb_exp)
  : fs_tab_(fs_tab)
  , nb_fs_(nb_fs)
  , exp_tab_(exp_tab)
  , nb_exp_(nb_exp)
{}

void Preset::init()
{
  EEPROM.get(eeprom_preset_number_start, number);
  load(number);
}

#warning "Preset::save : this is only a prototype
void Preset::save(uint8_t presetNumber)
{
#ifdef DEBUG
  Serial.print("saving to preset ");
  Serial.print(presetNumber,DEC);
  Serial.print("\n\r");
#endif //DEBUG
//manipulate EEprom here

  number = presetNumber;
  PresetData data;
  //fs
  for(uint8_t i=0; i< min(nb_fs_,nbFs); i++)
  {
    data.fsConfigs[i] = fs_tab_[i].get_config();
#ifdef DEBUG
    Serial.print("Fs ");
    Serial.print(i);
    Serial.print(" command ");
    Serial.print(data.fsConfigs[i].command,HEX);
    Serial.print(", mode ");
    Serial.print(data.fsConfigs[i].mode,HEX);
    Serial.print("\n\r");
#endif //DEBUG
  }
  //exp pedal
#warning "TODO"
  for(uint8_t i=0; i< min(nb_exp_,nbExp); i++)
  {
    data.expConfigs[i] = exp_tab_[i].get_config();
#ifdef DEBUG
    Serial.print("Exp ");
    Serial.print(i);
    Serial.print(" command ");
    Serial.print(data.fsConfigs[i].command,HEX);
    Serial.print(", mode ");
    Serial.print(data.fsConfigs[i].mode,HEX);
    Serial.print("\n\r");
#endif //DEBUG
  }

#ifdef DEBUG
  //Serial.print(eeprom_preset_number_start, number);
  Serial.print("addresse dans l'eeprom : ");
  Serial.print(eeprom_preset_bank_end + 1 -
      (presetNumber + 1 ) * sizeof(data), DEC);
  Serial.print("\n\r");
#endif

  //note : preset are stored in reverse order in the eeprom
  EEPROM.put(eeprom_preset_bank_end + 1 -
      (presetNumber + 1) * sizeof(data),data);
  EEPROM.put(eeprom_preset_number_start, number);
  isModified = false;
}

#warning "Preset::load : this is only a prototype
void Preset::load(uint8_t presetNumber)
{
#ifdef DEBUG
  Serial.print("loading preset ");
  Serial.print(presetNumber,DEC);
  Serial.print("\n\r");
#endif //DEBUG
//manipulate EEprom here
  number = presetNumber;
  PresetData data;

#ifdef DEBUG
  //Serial.print(eeprom_preset_number_start, number);
  Serial.print("addresse dans l'eeprom : ");
  Serial.print(eeprom_preset_bank_end + 1 -
      (presetNumber + 1 ) * sizeof(data), DEC);
  Serial.print("\n\r");
#endif

  EEPROM.put(eeprom_preset_number_start, number);
  //note : preset are stored in reverse order in the eeprom
  EEPROM.get(eeprom_preset_bank_end + 1 -
      (presetNumber + 1) * sizeof(data),data);
  //fs
  for(uint8_t i=0; i< min(nb_fs_,nbFs); i++)
  {
    fs_tab_[i].set_config(data.fsConfigs[i]);
#ifdef DEBUG
    Serial.print("Fs ");
    Serial.print(i);
    Serial.print(" command ");
    Serial.print(data.fsConfigs[i].command,HEX);
    Serial.print(", mode ");
    Serial.print(data.fsConfigs[i].mode,HEX);
    Serial.print("\n\r");
#endif //DEBUG
  }
  //exp pedal
#warning "TODO"
  for(uint8_t i=0; i< min(nb_exp_,nbExp); i++)
  {
    exp_tab_[i].set_config(data.expConfigs[i]);
#ifdef DEBUG
    Serial.print("Exp ");
    Serial.print(i);
    Serial.print(" command ");
    Serial.print(data.fsConfigs[i].command,HEX);
    Serial.print(", mode ");
    Serial.print(data.fsConfigs[i].mode,HEX);
    Serial.print("\n\r");
#endif //DEBUG
  }
  isModified = false;
}
