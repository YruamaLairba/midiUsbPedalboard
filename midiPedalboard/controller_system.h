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
};

#endif //CONTROLLER_SYSTEM_H
