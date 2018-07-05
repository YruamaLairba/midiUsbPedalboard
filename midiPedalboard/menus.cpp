#include "menus.h"


//MenuManager
void MenuManager::set_active(MenuBase* activated)
{
  pt_current = activated;
}

bool MenuManager::next()
{
  return pt_current->next();
}

bool MenuManager::prev()
{
  return pt_current->prev();
}

bool MenuManager::validate()
{
  return pt_current->validate();
}

bool MenuManager::cancel()
{
  return pt_current->cancel();
}

void MenuManager::print()
{
  pt_current->print();
}


//MenuBase
void MenuBase::activate()
{
  this->reset();
  manager->set_active(this);
}

//MenuFsCommand
//ctor
MenuFsCommand::MenuFsCommand(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset,
  Footswitch* fs,
  uint8_t nb_fs)
  : MenuBase(pt_manager,pt_parent),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset),
    fs_tab(fs),
    nb_fs(nb_fs){}

bool MenuFsCommand::next()
{
  bool res = false;
  if (this->selection < this->selectionMax)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
   return res;
}

bool MenuFsCommand::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
   return res;
}

bool MenuFsCommand::validate()
{
  fs_tab[pt_menuSwSelect->get_selectedFsNum()].set_command(selection);
  bool res = true;
  manager->set_active(parent);
  return res;
}

bool MenuFsCommand::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuFsCommand::reset()
{
  selection = pt_preset->get_fsCommand(
    pt_menuSwSelect->get_selectedFsNum());
  displayOffset = min(selection, (selectionMax - 3));
  return true;
}

void MenuFsCommand::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = displayOffset; i < (displayOffset + 4); i++)
  {
    if (selection == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
     if(i <= 127)
    {
      display.print(F("CC"));
      display.print(i, DEC);
    }
    display.print(F("\n\r"));
  }
  display.display();
}


//MenuFsMode
//ctor
MenuFsMode::MenuFsMode(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset,
  Footswitch* fs,
  uint8_t nb_fs)
  : MenuBase(pt_manager,pt_parent),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset),
    fs_tab(fs),
    nb_fs(nb_fs){}

bool MenuFsMode::next()
{
  bool res = false;
  if (this->selection < this->selectionMax)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
   return res;
}

bool MenuFsMode::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
 return res;
}

bool MenuFsMode::validate()
{
  fs_tab[pt_menuSwSelect->get_selectedFsNum()].set_mode(selection);
  bool res = true;
  manager->set_active(parent);
  return res;
}

bool MenuFsMode::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuFsMode::reset()
{
  selection = pt_preset->get_fsMode(
    pt_menuSwSelect->get_selectedFsNum());
  displayOffset = min(selection, (selectionMax - 3));
  return true;
}

void MenuFsMode::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = displayOffset; i < (displayOffset + 4); i++)
  {
    if (selection == i)
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

//MenuFsConfig

//ctor
MenuFsConfig::MenuFsConfig(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset,
  Footswitch* fs,
  uint8_t nb_fs)
  : MenuBase(pt_manager,pt_parent),
    menuFsCommand(pt_manager,this, pt_menuSwSelect, pt_preset, fs, nb_fs),
    menuFsMode(pt_manager,this, pt_menuSwSelect, pt_preset, fs, nb_fs),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset){}

bool MenuFsConfig::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuFsConfig::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuFsConfig::validate()
{
  switch (selection)
  {
    case 0:
      menuFsCommand.activate();
      break;
    case 1:
      menuFsMode.activate();
      break;
  }
  return true;
}

bool MenuFsConfig::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuFsConfig::reset()
{
  selection = 0;
  return true;
}

void MenuFsConfig::print()
{
  uint8_t fsNum = pt_menuSwSelect->get_selectedFsNum();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = 0; i< nbItems; i++)
  {
    if (selection == i)
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
        display.print(F("FS"));
        display.print(fsNum, DEC);
        display.print(F(" Cmd"));
        break;
      case 1:
        display.print(F("FS"));
        display.print(fsNum, DEC);
        display.print(F(" Mode"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

//MenuExpCommand
//ctor
MenuExpCommand::MenuExpCommand(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset)
  : MenuBase(pt_manager,pt_parent),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset){}

bool MenuExpCommand::next()
{
  bool res = false;
  if (this->selection < this->selectionMax)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
 return res;
}

bool MenuExpCommand::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}

bool MenuExpCommand::validate()
{
  pt_preset->set_expCommand(pt_menuSwSelect->get_selectedExpNum(),selection);
  bool res = true;
  manager->set_active(parent);
  return res;
}

bool MenuExpCommand::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuExpCommand::reset()
{
  selection = pt_preset->get_expCommand(
    pt_menuSwSelect->get_selectedExpNum());
  displayOffset = min(selection, (selectionMax - 3));
  return true;
}

void MenuExpCommand::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = displayOffset; i < (displayOffset + 4); i++)
  {
    if (selection == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    if(i <= 127)
    {
      display.print(F("CC"));
      display.print(i, DEC);
    }
    else if (i == 128)
    {
      display.print(F("PitchBend"));
    }
    display.print(F("\n\r"));
  }
  display.display();
}

//MenuExpMode
//ctor
MenuExpMode::MenuExpMode(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset)
  : MenuBase(pt_manager,pt_parent),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset){}

bool MenuExpMode::next()
{
  bool res = false;
  if (this->selection < this->selectionMax)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
 return res;
}

bool MenuExpMode::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
 return res;
}

bool MenuExpMode::validate()
{
  pt_preset->set_expMode(pt_menuSwSelect->get_selectedExpNum(),selection);
  bool res = true;
  manager->set_active(parent);
  return res;
}

bool MenuExpMode::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuExpMode::reset()
{
  selection = pt_preset->get_expMode(
    pt_menuSwSelect->get_selectedExpNum());
  return true;
}

void MenuExpMode::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for(uint8_t i = displayOffset; i < (displayOffset + 4); i++)
  {
    if (selection == i)
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
        display.print(F("normal"));
        break;
      case 1:
        display.print(F("reverse"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

//MenuExpConfig
//ctor
MenuExpConfig::MenuExpConfig(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset)
  : MenuBase(pt_manager, pt_parent),
    menuExpCommand(pt_manager, this, pt_menuSwSelect, pt_preset),
    menuExpMode(pt_manager, this, pt_menuSwSelect, pt_preset),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset){}

bool MenuExpConfig::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuExpConfig::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuExpConfig::validate()
{
  switch (selection)
  {
    case 0:
      menuExpCommand.activate();
      break;
    case 1:
      menuExpMode.activate();
      break;
  }
  return true;
}

bool MenuExpConfig::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuExpConfig::reset()
{
  selection = 0;
  return true;
}

void MenuExpConfig::print()
{
  uint8_t expNum = pt_menuSwSelect->get_selectedExpNum();
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = 0; i< nbItems; i++)
  {
    if (selection == i)
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
        display.print(F("EXP"));
        display.print(expNum, DEC);
        display.print(F(" Cmd"));
        break;
      case 1:
        display.print(F("EXP"));
        display.print(expNum, DEC);
        display.print(F(" Mode"));
        break;
    }
    display.print(F("\n\r"));
  }
  display.display();
}

//MenuSwSelect

//ctor
MenuSwSelect::MenuSwSelect(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  Preset* pt_preset,
  Footswitch* fs,
  uint8_t nb_fs)
  : MenuBase(pt_manager, pt_parent),
    fsConfig(pt_manager, this, this, pt_preset, fs, nb_fs),
    expConfig(pt_manager, this, this, pt_preset),
    pt_preset(pt_preset){}

bool MenuSwSelect::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
  return res;
}

bool MenuSwSelect::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}

bool MenuSwSelect::validate()
{
  bool res = false;
  if(selection < nbFs)
  {
    fsConfig.activate();
    res = true;
  }
  else if (selection < (nbFs + nbExp))
  {
    expConfig.activate();
    res = true;
  }
  return res;
}

bool MenuSwSelect::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuSwSelect::reset()
{
  selection = 0;
  displayOffset = 0;
  return true;
}

void MenuSwSelect::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  if (pt_preset != NULL)
  {
    for (int i = displayOffset; i< (displayOffset + 4); i++)
    {
      if (selection == i)
      {
        display.setTextColor(BLACK,WHITE);
      }
      else
      {
        display.setTextColor(WHITE,BLACK);
      }
      if (i < nbFs)
      {
        display.print(F("FS "));
        display.print(i, DEC);
      }
      else if (i < (nbFs + nbExp))
      {
        display.print(F("Exp "));
        display.print(i - nbFs, DEC);
      }
      display.print(F("\n\r"));
    }
  }
  display.display();
}

uint8_t MenuSwSelect::get_selectedFsNum()
{
  //normal case
  if(selection < nbFs)
  {
    return selection;
  }
  //error case
  else
  {
    return -1;
  }
}

uint8_t MenuSwSelect::get_selectedExpNum()
{
  //normal case
  if((selection >= nbFs) and (selection < (nbFs + nbExp)))
  {
    return selection - nbFs;
  }
  //error case
  else
  {
    return -1;
  }
}


//MenuPresetLoad

//ctor
MenuPresetLoad::MenuPresetLoad(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  Preset* pt_preset)
  : MenuBase(pt_manager, pt_parent),
    pt_preset(pt_preset)
    {}

void MenuPresetLoad::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuPresetLoad::next()
{
  bool res = false;
  if (this->selection < pt_preset->get_nbPreset() -1)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
  return res;
}

bool MenuPresetLoad::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}

#warning "MenuPrestLoad: this is only a prototype"
bool MenuPresetLoad::validate()
{
  pt_preset->load(selection);
  manager->set_active(parent);
  return true;
}

bool MenuPresetLoad::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuPresetLoad::reset()
{
  selection = 0;
  displayOffset = 0;
  return true;
}

void MenuPresetLoad::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = displayOffset; i< (displayOffset + 4); i++)
  {
    if (selection == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Lreset "));
    display.print(i,DEC);
    display.print(F("\n\r")); 
  }
  display.display();
}

//MenuPresetSave

//ctor
MenuPresetSave::MenuPresetSave(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  Preset* pt_preset)
  : MenuBase(pt_manager, pt_parent),
    pt_preset(pt_preset)
    {}

void MenuPresetSave::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuPresetSave::next()
{
  bool res = false;
  if (this->selection < pt_preset->get_nbPreset() -1)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
  return res;
}

bool MenuPresetSave::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}

#warning "MenuPresetSave: this is only a prototype"
bool MenuPresetSave::validate()
{
  pt_preset->save(selection);
  manager->set_active(parent);
}

bool MenuPresetSave::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuPresetSave::reset()
{
  selection = 0;
  displayOffset = 0;
  return true;
}

void MenuPresetSave::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = displayOffset; i< (displayOffset + 4); i++)
  {
    if (selection == i)
    {
      display.setTextColor(BLACK,WHITE);
    }
    else
    {
      display.setTextColor(WHITE,BLACK);
    }
    display.print(F("Preset "));
    display.print(i,DEC);
    display.print(F("\n\r")); 
  }
  display.display();
}


//MenuGeneralSetting

//ctor
MenuGeneralSetting::MenuGeneralSetting(MenuManager* pt_manager, MenuBase* pt_parent)
  : MenuBase(pt_manager, pt_parent),
    nbItems(2)
    {}

void MenuGeneralSetting::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuGeneralSetting::next()
{
  bool res = false;
  if (this->selection < this->nbItems-1)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4 ))
  {
    displayOffset++;
  }
  return res;
}

bool MenuGeneralSetting::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}

#warning "MenuGeneralSetting: don't forget submenu activation"
bool MenuGeneralSetting::validate()
{
  switch(selection)
  {
    case 0:
      break;
    case 1:
      break;
  }
  return true;
}

bool MenuGeneralSetting::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuGeneralSetting::reset()
{
  selection = 0;
  displayOffset = 0;
  return true;
}

void MenuGeneralSetting::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = displayOffset; i< (displayOffset + 4) and i<nbItems; i++)
  {
    if (selection == i)
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



//MenuMainConf

//ctor
MenuMainConf::MenuMainConf(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  Preset* pt_preset,
  Footswitch* fs,
  uint8_t nb_fs)
  : MenuBase(pt_manager,pt_parent),
    swSelect(pt_manager, this, pt_preset, fs, nb_fs),
    presetLoad(pt_manager, this, pt_preset),
    presetSave(pt_manager, this, pt_preset),
    generalSetting(pt_manager, this) {}

void MenuMainConf::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuMainConf::next()
{
  bool res = false;
  if (this->selection < this->nbItems - 1)
  {
    this->selection++;
    res = true;
  }
  if (selection >= (displayOffset + 4))
  {
    displayOffset++;
  }
  return res;
}

bool MenuMainConf::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  if (selection < displayOffset)
  {
    displayOffset--;
  }
  return res;
}


bool MenuMainConf::validate()
{
  bool res = false;
  switch (selection)
  {
    case 0:
      swSelect.activate();
      res=true;
      break;
    case 1:
      presetLoad.activate();
      res=true;
      break;
    case 2:
      presetSave.activate();
      res=true;
      break;
    case 3:
      generalSetting.activate();
      res=true;
      break;
  }
  return res;
}

bool MenuMainConf::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuMainConf::reset()
{
  selection = 0;
  return true;
}

void MenuMainConf::print()
{
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i = displayOffset; i< (displayOffset + 4); i++)
  {
    if (selection == i)
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
        display.print(F("SW set"));
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

