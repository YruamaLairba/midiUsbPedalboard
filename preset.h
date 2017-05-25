#ifndef PRESET_H
#define PRESET_H

#include <stdint.h>
#include "footswitch.h"

typedef uint8_t FsMode;
typedef uint8_t FsCommand;
struct FsConfig
{
  FsMode fsMode;
  FsCommand fsCommand;
};

typedef uint8_t ExpMode;
typedef uint8_t ExpCommand;
struct ExpConfig
{
  ExpMode expMode;
  ExpCommand expCommand;
};

#warning "replace litteral values by an abstract value"
class Preset
{
  private:
    FsConfig fsConfigs [4];
    static const uint8_t nbFsConfigs = 4 ;
    ExpConfig expConfigs [1];
    static const uint8_t nbExpConfigs = 1;
    uint8_t number; //number of the currently loaded preset
    static const uint8_t nbPreset = 128;
    bool isModified; //is the current preset modified ?
  public:
    Preset();

    //void init(); //for startup initialization

    FsMode get_fsMode(uint8_t fsNumber);
    void set_fsMode(uint8_t fsNumber, FsMode fsMode);
    FsCommand get_fsCommand(uint8_t fsNumber);
    void set_fsCommand(uint8_t fsNumber, FsCommand fsCommand);
    ExpMode get_expMode(uint8_t expNumber);
    void set_expMode(uint8_t expNumber, ExpMode expMode);
    ExpCommand get_expCommand(uint8_t expNumber);
    void set_expCommand(uint8_t expNumber, ExpCommand expCommand);
    uint8_t get_nbFsConfigs(){return nbFsConfigs;}
    uint8_t get_nbExpConfigs(){return nbExpConfigs;}

    //void save(int8_t presetNumber);
    //void load(int8_t presetNumber);
    //uint8_t get_presetNumber();
    //bool isMofified();
};





#endif //PRESET_H
