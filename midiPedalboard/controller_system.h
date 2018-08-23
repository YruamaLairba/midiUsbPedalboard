#ifndef CONTROLLER_SYSTEM_H
#define CONTROLLER_SYSTEM_H

#include "setup.h"
#include "footswitch.h"
#include "exp_pedal.h"
#include "global_setting.h"
#include "preset.h"

#include <stdint.h>

class ControllerSystem
{
  private:
    Footswitch fs_tab_[nbFs];
    ExpPedal exp_tab_[nbExp];
    GlobalSetting global_setting_;
    Preset preset_;
    static const uint8_t nb_fs_ = nbFs;
    static const uint8_t nb_exp_ = nbExp;
  public:
    ControllerSystem();
    void init();
    void process();
    //number accessor
    static uint8_t get_nb_fs(){return nb_fs_;}
    static uint8_t get_nb_exp(){return nb_exp_;}
    //accessor for footswitch
    uint8_t get_fs_command(uint8_t fs_num);
    void set_fs_command(uint8_t fs_num, uint8_t fs_cmd);
    uint8_t get_fs_mode(uint8_t fs_num);
    void set_fs_mode(uint8_t fs_num, uint8_t fs_mode);
    //accessor for exp pedal
    uint8_t get_exp_command(uint8_t exp_num);
    void set_exp_command(uint8_t exp_num, uint8_t exp_cmd);
    uint8_t get_exp_mode(uint8_t exp_num);
    void set_exp_mode(uint8_t exp_num, uint8_t exp_mode);
    //preset
    uint8_t get_nb_preset();
    uint8_t get_current_preset();
    void load_preset(uint8_t preset_num);
    void save_preset(uint8_t preset_num);
    //midi channel
    uint8_t get_midi_channel();
    void set_midi_channel(uint8_t channel);
};

#endif //CONTROLLER_SYSTEM_H
