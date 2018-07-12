#ifndef PRESET_H
#define PRESET_H

#include <stdint.h>
#include "setup.h"
#include "footswitch.h"
#include "EEPROM.h"

typedef uint8_t FsMode;
typedef uint8_t FsCommand;

typedef uint8_t ExpMode;
typedef uint8_t ExpCommand;
struct ExpConfig
{
  ExpMode expMode;
  ExpCommand expCommand;
};

struct PresetData
{
  FsConfig fsConfigs [nbFs];
  ExpConfig expConfigs [nbExp];
};


#warning "replace litteral values by an abstract value"
class Preset
{
  private:
    Footswitch* fs_tab_;
    uint8_t nb_fs_;
    static const uint8_t nbPreset = (E2END + 1)/sizeof(PresetData);
    uint8_t number; //number of the currently loaded preset
    bool isModified; //is the current preset modified ?
  public:
    Preset();
    Preset(Footswitch* fs_tab, uint8_t nb_fs);

    //void init(); //for startup initialization

    void save(uint8_t presetNumber);
    void load(uint8_t presetNumber);
    uint8_t get_nbPreset(){return nbPreset;};
    uint8_t get_presetNumber(){return number;};
    bool isMofified(){return isModified;};
};
#endif //PRESET_H
