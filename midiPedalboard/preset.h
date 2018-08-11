#ifndef PRESET_H
#define PRESET_H

#include "setup.h"
#include "footswitch.h"
#include "exp_pedal.h"
#include "eeprom_config.h"

#include <stdint.h>

typedef uint8_t FsMode;
typedef uint8_t FsCommand;

typedef uint8_t ExpMode;
typedef uint8_t ExpCommand;

struct PresetData
{
  FsConfig fsConfigs [nbFs];
  ExpConfig expConfigs [nbExp];
};

class Preset
{
  private:
    Footswitch* fs_tab_;
    uint8_t nb_fs_;
    ExpPedal* exp_tab_;
    uint8_t nb_exp_;
    static const uint8_t nbPreset = (eeprom_preset_bank_end + 1
        - eeprom_preset_bank_start)/sizeof(PresetData);
    uint8_t number; //number of the currently loaded preset
    bool isModified; //is the current preset modified ?
  public:
    Preset();
    Preset(Footswitch* fs_tab, uint8_t nb_fs,
        ExpPedal* exp_tab, uint8_t nb_exp_);

    void init(); //for startup initialization

    void save(uint8_t presetNumber);
    void load(uint8_t presetNumber);
    uint8_t get_nbPreset(){return nbPreset;};
    uint8_t get_presetNumber(){return number;};
    bool isMofified(){return isModified;};
};
#endif //PRESET_H
