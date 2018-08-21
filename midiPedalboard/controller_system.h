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
    //accessor for footswitch
    void get_fs_command(uint8_t fs_num);
    void set_fs_command(uint8_t fs_num, uint8_t fs_cmd);
    void get_fs_mode(uint8_t fs_num);
    void set_fs_mode(uint8_t fs_num, uint8_t fs_mode);
    //accessor for exp pedal
    void get_exp_command(uint8_t exp_num);
    void set_exp_command(uint8_t exp_num, uint8_t exp_cmd);
    void get_exp_mode(uint8_t exp_num);
    void set_exp_mode(uint8_t exp_num, uint8_t exp_mode);
};

#endif //CONTROLLER_SYSTEM_H
