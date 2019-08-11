#ifndef CONTROLLER_SYSTEM_H
#define CONTROLLER_SYSTEM_H

#include "setup.h"
#include "footswitch.h"
#include "exp_pedal.h"
#include "eeprom_config.h"


#include <stdint.h>

//a block of preset data in eeprom
struct PresetData
{
  FsConfig fsConfigs [nbFs];
  ExpConfig expConfigs [nbExp];
};

class ControllerSystem
{
  private:
    Footswitch fs_tab_[nbFs];
    ExpPedal exp_tab_[nbExp];
    uint8_t current_preset_;//the number of the currently loaded present
    bool is_preset_modified_;//is the current preset modified ?
    uint8_t midi_channel_;
    static const uint8_t nb_fs_ = nbFs;
    static const uint8_t nb_exp_ = nbExp;
    static const uint8_t nb_preset_ = (eeprom_preset_bank_end + 1
        - eeprom_preset_bank_start)/sizeof(PresetData);
  public:
    ControllerSystem();
    void init();
    void process();
    //number accessor
    static uint8_t get_nb_fs(){return nb_fs_;}
    static uint8_t get_nb_exp(){return nb_exp_;}
    //accessor for footswitch
    Footswitch* get_fs(uint8_t fs_num);
    fsCmdTyp_t get_fs_cmd_typ(uint8_t fs_num);
    void set_fs_cmd_typ(uint8_t fs_num, fsCmdTyp_t fs_cmd_typ);
    uint8_t get_fs_command(uint8_t fs_num);
    void set_fs_command(uint8_t fs_num, uint8_t fs_cmd);
    uint8_t get_fs_mode(uint8_t fs_num);
    void set_fs_mode(uint8_t fs_num, uint8_t fs_mode);
    //accessor for exp pedal
    expCmdTyp_t get_exp_cmd_typ(uint8_t exp_num);
    void set_exp_cmd_typ(uint8_t exp_num, expCmdTyp_t exp_cmd_typ);
    uint8_t get_exp_command(uint8_t exp_num);
    void set_exp_command(uint8_t exp_num, uint8_t exp_cmd);
    uint8_t get_exp_mode(uint8_t exp_num);
    void set_exp_mode(uint8_t exp_num, uint8_t exp_mode);
    int16_t get_exp_raw_val(uint8_t exp_num);
    void exp_reset(uint8_t exp_num);
    //preset
    uint8_t get_nb_preset();
    uint8_t get_current_preset();
    bool is_preset_modified();
    void load_preset(uint8_t preset_num);
    void save_preset(uint8_t preset_num);
    //midi channel
    uint8_t get_midi_channel();
    void set_midi_channel(uint8_t channel);
};

#endif //CONTROLLER_SYSTEM_H
