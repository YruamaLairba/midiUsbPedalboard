#include "preset.h"

#ifdef DEBUG
#include <Arduino.h>
#endif //DEBUG

//ctor
Preset::Preset(){}

Preset::Preset(Footswitch* fs_tab,uint8_t nb_fs)
  : fs_tab_(fs_tab)
  ,nb_fs_(nb_fs)
{}

//void Preset::init()
//{
//}

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
  /*
  for(i=0; i< min(nb_exp_,nbExp); i++)
  {
    data.expConfigs[i] = exp_tab_[i].get_config();
  }
  */
  EEPROM.put(E2END + 1 - presetNumber*sizeof(data),data);
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
  EEPROM.get(E2END + 1 - presetNumber*sizeof(data), data);
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
  /*
  for(i=0; i< min(nb_exp,nbExp); i++)
  {
    exp_tab_[i].set_config(data.expConfigs[i]);
  }
  */
  isModified = false;
}
