#include "menu_system.h"

void print_fs_mmc(fsMmc_t mmc_cmd)
{
  switch (mmc_cmd)
  {
    case fsMmc_t::play:
      display.print(F("play"));
      break;
    case fsMmc_t::stop:
      display.print(F("stop"));
      break;
    case fsMmc_t::play_stop:
      display.print(F("play/stop"));
      break;
    case fsMmc_t::record_punch:
      display.print(F("record"));
      break;
    case fsMmc_t::record_punch_stop:
      display.print(F("record/stop"));
      break;
    case fsMmc_t::pause:
      display.print(F("pause"));
      break;
    case fsMmc_t::fast_forward:
      display.print(F("fast_forward"));
      break;
    case fsMmc_t::rewind:
      display.print(F("backward"));
      break;
  }
}

MenuSystem::MenuBase::MenuBase(MenuSystem* pt_menu_system)
  : pt_menu_system_(pt_menu_system)
{}

MenuSystem::MenuTemplate::MenuTemplate(MenuSystem* pt_menu_system)
  : MenuBase(pt_menu_system)
  , selection_(0)
  , display_offset_(0)
{}

void MenuSystem::MenuTemplate::reset()
{
  selection_ = 0;
  display_offset_ = 0;
}

void MenuSystem::MenuTemplate::select_next()
{
  if (selection_ < get_nb_item()-1)
  {
    selection_++;
  }
  if (selection_ >= (display_offset_ + 4 ))
  {
    display_offset_++;
  }
  print();
}

void MenuSystem::MenuTemplate::select_prev()
{
  if (selection_ > 0)
  {
    selection_--;
  }
  if (selection_ < display_offset_)
  {
    display_offset_--;
  }
  print();
}

MenuSystem::SubMenuTemplate::SubMenuTemplate(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent)
  : MenuTemplate(pt_menu_system)
  , pt_parent_(pt_parent)
{}

void MenuSystem::SubMenuTemplate::activate()
{
  pt_menu_system_->set_active(this);
}

void MenuSystem::SubMenuTemplate::cancel()
{
  pt_menu_system_->set_active(pt_parent_);
}

MenuSystem::MenuFsCmdTyp::MenuFsCmdTyp(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsCmdTyp::get_nb_item()
{
  return static_cast<uint8_t>(fsCmdTyp_t::MAX)+1;
}

void MenuSystem::MenuFsCmdTyp::activate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  selection_ =  static_cast<uint8_t>(
      pt_menu_system_->pt_controller_system_->get_fs_cmd_typ(fs));
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuFsCmdTyp::validate()
{
  uint8_t fsNum = pt_menu_controller_setting_->get_selected_fs();
  Footswitch* pt_fs = pt_menu_system_->pt_controller_system_->get_fs(fsNum);
  if (pt_fs->get_cmd_typ() != static_cast<fsCmdTyp_t>(selection_))
  {
    pt_fs->reset();
    pt_fs->set_cmd_typ(static_cast<fsCmdTyp_t>(selection_));
  }
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuFsCmdTyp::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    switch (i)
    {
      case 0:
        display.print(F("Ctl Change\n\r"));
        break;
      case 1:
        display.print(F("Pgm Change\n\r"));
        break;
      case 2:
        display.print(F("MMC Cmd\n\r"));
        break;
    }
  }
  display.display();
}

MenuSystem::MenuFsCCVal::MenuFsCCVal(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsCCVal::get_nb_item(){return 128;}

void MenuSystem::MenuFsCCVal::activate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  selection_ =  pt_menu_system_->pt_controller_system_->get_fs_command(fs);
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuFsCCVal::validate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  pt_menu_system_->pt_controller_system_->set_fs_command(fs, selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuFsCCVal::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("CC"));
    display.print(i, DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuFsMMCVal::MenuFsMMCVal(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsMMCVal::get_nb_item()
{
  return static_cast<uint8_t>(fsMmc_t::MAX)+1;
}

void MenuSystem::MenuFsMMCVal::activate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  selection_ =  pt_menu_system_->pt_controller_system_->get_fs_command(fs);
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuFsMMCVal::validate()
{
  uint8_t fsNum = pt_menu_controller_setting_->get_selected_fs();
  pt_menu_system_->pt_controller_system_->get_fs(fsNum)->
    set_mmc(static_cast<fsMmc_t>(selection_));
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuFsMMCVal::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    print_fs_mmc(static_cast<fsMmc_t>(i));
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuFsPGMVal::MenuFsPGMVal(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsPGMVal::get_nb_item(){return 128;}

void MenuSystem::MenuFsPGMVal::activate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  selection_ =  pt_menu_system_->pt_controller_system_->get_fs_command(fs);
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuFsPGMVal::validate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  pt_menu_system_->pt_controller_system_->set_fs_command(fs, selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuFsPGMVal::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("PGM"));
    display.print(i, DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuFsMode::MenuFsMode(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsMode::get_nb_item(){return fsMode::nb_item;}

void MenuSystem::MenuFsMode::activate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  selection_ =  pt_menu_system_->pt_controller_system_->get_fs_mode(fs);
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuFsMode::validate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  pt_menu_system_->pt_controller_system_->set_fs_mode(fs, selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuFsMode::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = display_offset_; i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
  switch (i)
    {
      case fsMode::toggle_off:
        display.print(F("tog off"));
        break;
      case fsMode::toggle_on:
        display.print(F("tog on"));
        break;
      case fsMode::momentary_off:
        display.print(F("mom (off)"));
        break;
      case fsMode::momentary_on:
        display.print(F("mom (on)"));
        break;
      case fsMode::single_off:
        display.print(F("sing off"));
        break;
      case fsMode::single_on:
        display.print(F("sing on"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuExpCmdTyp::MenuExpCmdTyp(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpCmdTyp::get_nb_item()
{
  return static_cast<uint8_t>(expCmdTyp_t::MAX)+1;
}

void MenuSystem::MenuExpCmdTyp::activate()
{
  uint8_t exp_num = pt_menu_controller_setting_->get_selected_exp();
  selection_ =  static_cast<uint8_t>(
      pt_menu_system_->pt_controller_system_->get_exp_cmd_typ(exp_num));
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuExpCmdTyp::validate()
{
  uint8_t exp_num = pt_menu_controller_setting_->get_selected_exp();
  expCmdTyp_t cur_cmd_typ =
      pt_menu_system_->pt_controller_system_->get_exp_cmd_typ(exp_num);
  if (cur_cmd_typ != static_cast<expCmdTyp_t>(selection_))
  {
    pt_menu_system_->pt_controller_system_->exp_reset(exp_num);
    pt_menu_system_->pt_controller_system_->
      set_exp_cmd_typ(exp_num,static_cast<expCmdTyp_t>(selection_));
  }
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuExpCmdTyp::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    switch (i)
    {
      case 0:
        display.print(F("none\n\r"));
        break;
      case 1:
        display.print(F("Ctl Change\n\r"));
        break;
      case 2:
        display.print(F("Pitch Bend\n\r"));
        break;
    }
  }
  display.display();
}

MenuSystem::MenuExpCommand::MenuExpCommand(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpCommand::get_nb_item(){return 128;}

void MenuSystem::MenuExpCommand::activate()
{
  uint8_t exp = pt_menu_controller_setting_->get_selected_exp();
  selection_ =  pt_menu_system_->pt_controller_system_->get_exp_command(exp);
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuExpCommand::validate()
{
  uint8_t exp = pt_menu_controller_setting_->get_selected_exp();
  pt_menu_system_->pt_controller_system_->set_exp_command(exp, selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuExpCommand::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("CC"));
    display.print(i, DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuExpMode::MenuExpMode(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpMode::get_nb_item(){return expMode::nb_item;}

void MenuSystem::MenuExpMode::activate()
{
  uint8_t exp = pt_menu_controller_setting_->get_selected_exp();
  selection_ =  pt_menu_system_->pt_controller_system_->get_exp_mode(exp);
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuExpMode::validate()
{
  uint8_t exp = pt_menu_controller_setting_->get_selected_exp();
  pt_menu_system_->pt_controller_system_->set_exp_mode(exp, selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuExpMode::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = display_offset_; i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
  switch (i)
    {
      case expMode::normal:
        display.print(F("normal"));
        break;
      case expMode::reverse:
        display.print(F("reverse"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuFsSetting::MenuFsSetting(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_fs_cmd_typ_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_fs_cc_val_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_fs_pgm_val_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_fs_mmc_val_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_fs_mode_(pt_menu_system, this, pt_menu_controller_setting)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuFsSetting::get_nb_item()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  fsCmdTyp_t cmd_typ = 
    pt_menu_system_->pt_controller_system_->get_fs_cmd_typ(fs);

  switch(cmd_typ)
  {
    case fsCmdTyp_t::cc:
      return 3;
    case fsCmdTyp_t::pgm:
      return 2;
    case fsCmdTyp_t::mmc:
      return 2;
    default:
      return 0;//this should never reached
  }
}

void MenuSystem::MenuFsSetting::validate()
{
  uint8_t fs = pt_menu_controller_setting_->get_selected_fs();
  fsCmdTyp_t cmd_typ = 
    pt_menu_system_->pt_controller_system_->get_fs_cmd_typ(fs);
  switch(selection_)
  {
    case 0:
      menu_fs_cmd_typ_.activate();
      break;
    case 1:
      switch(cmd_typ)
      {
        case fsCmdTyp_t::cc:
          menu_fs_cc_val_.activate();
          break;
        case fsCmdTyp_t::pgm:
          menu_fs_pgm_val_.activate();
          break;
        case fsCmdTyp_t::mmc:
          menu_fs_mmc_val_.activate();
          break;
      }
      break;
    case 2:
      menu_fs_mode_.activate();
      break;
  }
}

void MenuSystem::MenuFsSetting::print()
{
  uint8_t fsNum = pt_menu_controller_setting_->get_selected_fs();
  fsCmdTyp_t cmd_typ =
    pt_menu_system_->pt_controller_system_->get_fs_cmd_typ(fsNum);
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("FS"));
    display.print(fsNum, DEC);
    switch (i)
    {
      case 0:
        display.print(F(" CmdTyp"));
        break;
      case 1:
        switch(cmd_typ)
        {
          case fsCmdTyp_t::cc:
            display.print(F(" CCVal"));
            break;
          case fsCmdTyp_t::pgm:
            display.print(F(" PGMVal"));
            break;
          case fsCmdTyp_t::mmc:
            display.print(F(" MMCVal"));
            break;
        }
        break;
      case 2:
        display.print(F(" CCMode"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuExpSetting::MenuExpSetting(
    MenuSystem* pt_menu_system,
    MenuBase* pt_parent,
    MenuControllerSetting* pt_menu_controller_setting)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_exp_command_(pt_menu_system, this, pt_menu_controller_setting)
  , menu_exp_mode_(pt_menu_system, this, pt_menu_controller_setting)
  , pt_menu_controller_setting_(pt_menu_controller_setting)
{}

uint8_t MenuSystem::MenuExpSetting::get_nb_item(){return 2;}

void MenuSystem::MenuExpSetting::validate()
{
  switch(selection_)
  {
    case 0:
      menu_exp_command_.activate();
      break;
    case 1:
      menu_exp_mode_.activate();
      break;
  }
}


void MenuSystem::MenuExpSetting::print()
{
  uint8_t expNum = pt_menu_controller_setting_->get_selected_exp();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Exp"));
    display.print(expNum, DEC);
    switch (i)
    {
      case 0:
        display.print(F(" Cmd"));
        break;
      case 1:
        display.print(F(" Mode"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuControllerSetting::MenuControllerSetting(
    MenuSystem* pt_menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_fs_setting_(pt_menu_system,this,this)
  , menu_exp_setting_(pt_menu_system,this,this)
{}

uint8_t MenuSystem::MenuControllerSetting::get_nb_item()
{
  return pt_menu_system_->pt_controller_system_->get_nb_fs() +
    pt_menu_system_->pt_controller_system_->get_nb_exp() ;
}

void MenuSystem::MenuControllerSetting::validate()
{
  uint8_t nb_fs = pt_menu_system_->pt_controller_system_->get_nb_fs();
  uint8_t nb_exp = pt_menu_system_->pt_controller_system_->get_nb_exp();
  if(selection_ < nb_fs)
  {
    menu_fs_setting_.activate();
  }
  else if (selection_ >= nb_fs && selection_ < nb_fs + nb_exp)
  {
    menu_exp_setting_.activate();
  }
}

void MenuSystem::MenuControllerSetting::print()
{
  uint8_t nb_fs = pt_menu_system_->pt_controller_system_->get_nb_fs();
  uint8_t nb_exp = pt_menu_system_->pt_controller_system_->get_nb_exp();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    if (i < nb_fs)
    {
      display.print(F("FS "));
      display.print(i, DEC);
    }
    else if (i < (nb_fs + nb_exp))
    {
      display.print(F("Exp "));
      display.print(i - nb_fs, DEC);
    }
    display.print(F("\n\r"));
  }
  display.display();
}

uint8_t MenuSystem::MenuControllerSetting::get_selected_fs()
{
  return selection_;
}

uint8_t MenuSystem::MenuControllerSetting::get_selected_exp()
{
  return selection_ -
    pt_menu_system_->pt_controller_system_->get_nb_fs();
}

MenuSystem::MenuPresetLoad::MenuPresetLoad(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

void MenuSystem::MenuPresetLoad::activate()
{
  selection_ =  pt_menu_system_->pt_controller_system_->get_current_preset();
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

uint8_t MenuSystem::MenuPresetLoad::get_nb_item()
{
  return pt_menu_system_->pt_controller_system_->get_nb_preset();
}

void MenuSystem::MenuPresetLoad::validate()
{
  pt_menu_system_->pt_controller_system_->load_preset(selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuPresetLoad::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Load "));
    display.print(i,DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuPresetSave::MenuPresetSave(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuSystem::MenuPresetSave::get_nb_item()
{
  return pt_menu_system_->pt_controller_system_->get_nb_preset();
}

void MenuSystem::MenuPresetSave::activate()
{
  selection_ =  pt_menu_system_->pt_controller_system_->get_current_preset();
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuPresetSave::validate()
{
  pt_menu_system_->pt_controller_system_->save_preset(selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuPresetSave::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Save to "));
    display.print(i,DEC);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuMidiChannel::MenuMidiChannel(
    MenuSystem* menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(menu_system, pt_parent)
{}

uint8_t MenuSystem::MenuMidiChannel::get_nb_item(){return 16;}

void MenuSystem::MenuMidiChannel::activate()
{
  selection_ =  pt_menu_system_->pt_controller_system_->get_midi_channel();
  display_offset_ = (get_nb_item() < 4)?0:min(selection_, get_nb_item()-4);
  SubMenuTemplate::activate();
}

void MenuSystem::MenuMidiChannel::validate()
{
  pt_menu_system_->pt_controller_system_->set_midi_channel(selection_);
  pt_menu_system_->set_active(pt_parent_);
}

void MenuSystem::MenuMidiChannel::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Channel "));
    display.print(i + 1);
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuGlobalSetting::MenuGlobalSetting(
    MenuSystem* pt_menu_system, MenuBase* pt_parent)
  : SubMenuTemplate(pt_menu_system, pt_parent)
  , menu_midi_channel_(pt_menu_system, this)
{}

uint8_t MenuSystem::MenuGlobalSetting::get_nb_item(){return 2;}

void MenuSystem::MenuGlobalSetting::validate()
{
  switch(selection_)
  {
    case 0:
      menu_midi_channel_.activate();
      break;
  }
}

void MenuSystem::MenuGlobalSetting::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < display_offset_ + 4; i++)
  {
    if (selection_ == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    switch(i)
    {
      case 0:
        display.print(F("Midi chan"));
        break;
      case 1:
        display.print(F("Exp cal"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuConf::MenuConf(MenuSystem* menu_system)
  : MenuTemplate(menu_system)
  , menu_controller_setting_(menu_system,this)
  , menu_preset_load_(menu_system,this)
  , menu_preset_save_(menu_system,this)
  , menu_global_setting_(menu_system,this)
{}

uint8_t MenuSystem::MenuConf::get_nb_item(){return 4;}

void MenuSystem::MenuConf::validate()
{
  switch(selection_)
  {
    case 0:
      menu_controller_setting_.activate();
      break;
    case 1:
      menu_preset_load_.activate();
      break;
    case 2:
      menu_preset_save_.activate();
      break;
    case 3:
      menu_global_setting_.activate();
      break;
  }
}

void MenuSystem::MenuConf::cancel()
{
}

void MenuSystem::MenuConf::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = display_offset_;
      i < get_nb_item() && i < (display_offset_ + 4); i++)
  {
    if (selection_ == i)
      {
        display.setTextColor(BLACK,WHITE);
      }
      else
      {
        display.setTextColor(WHITE,BLACK);
      }
      switch(i)
    {
      case 0:
        display.print(F("Cont. set"));
        break;
      case 1:
        display.print(F("Load Pres"));
        break;
      case 2:
        display.print(F("Save Pres"));
        break;
      case 3:
        display.print(F("Gen. set"));
        break;
      default:
        break;
    }
   display.print(F("\n\r"));
  }
  display.display();
}

MenuSystem::MenuSystem(ControllerSystem* pt_controller_system)
  : root_(this)
  , pt_current_(&root_)
  , rotary_encoder_(rotaryPinA,rotaryPinB)
  , button_ok_(buttonOkPin)
  , button_cancel_(buttonCancelPin)
  , pt_controller_system_(pt_controller_system)
{

}

void MenuSystem::init()
{
  root_.print();
}

void MenuSystem::set_active(MenuBase* activated)
{
  pt_current_ = activated;
  pt_current_->print();
}

void MenuSystem::process()
{
  switch(rotary_encoder_.read())
  {
    case 1:
      pt_current_->select_next();
      break;
    case -1:
      pt_current_->select_prev();
      break;
  }
  if(button_ok_.read()== PushButtonVal::pressed)
  {
    pt_current_->validate();
  }
  if(button_cancel_.read()== PushButtonVal::pressed)
  {
    pt_current_->cancel();
  }
}

