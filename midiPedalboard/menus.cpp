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
  Preset* pt_preset)
  : MenuBase(pt_manager,pt_parent),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset){}

bool MenuFsCommand::next()
{
  bool res = false;
  if (this->selection < this->selectionMax)
  {
    this->selection++;
    res = true;
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
  return res;
}

bool MenuFsCommand::validate()
{
  pt_preset->set_fsCommand(pt_menuSwSelect->get_selectedFsNum(),selection);
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
  return true;
}

void MenuFsCommand::print()
{
  if(selection <= 127)
  {
    Serial.print(F("CC"));
    Serial.print(selection,DEC);
  }
  Serial.print(F("\n\r"));
}


//MenuFsMode
//ctor
MenuFsMode::MenuFsMode(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset)
  : MenuBase(pt_manager,pt_parent),
    pt_menuSwSelect(pt_menuSwSelect),
    pt_preset(pt_preset){}

bool MenuFsMode::next()
{
  bool res = false;
  if (this->selection < this->selectionMax)
  {
    this->selection++;
    res = true;
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
  return res;
}

bool MenuFsMode::validate()
{
  pt_preset->set_fsMode(pt_menuSwSelect->get_selectedFsNum(),selection);
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
  return true;
}

void MenuFsMode::print()
{
  switch (selection)
  {
    case 0:
      Serial.print(F("tog off"));
      break;
    case 1:
      Serial.print(F("tog on"));
      break;
    case 2:
      Serial.print(F("mom pre"));
      break;
    case 3:
      Serial.print(F("mom dp"));
      break;
    case 4:
      Serial.print(F("sing on"));
      break;
    case 5:
      Serial.print(F("sing off"));
      break;
  }
  Serial.print(F("\n\r"));
}

//MenuFsConfig

//ctor
MenuFsConfig::MenuFsConfig(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  MenuSwSelect* pt_menuSwSelect,
  Preset* pt_preset)
  : MenuBase(pt_manager,pt_parent),
    menuFsCommand(pt_manager,this, pt_menuSwSelect, pt_preset),
    menuFsMode(pt_manager,this, pt_menuSwSelect, pt_preset),
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
  for (int i = 0; i< nbItems; i++)
  {
    switch (i)
    {
      case 0:
        Serial.print(F("FS"));
        Serial.print(fsNum, DEC);
        Serial.print(F(" Cmd"));
        break;
      case 1:
        Serial.print(F("FS"));
        Serial.print(fsNum, DEC);
        Serial.print(F(" Mode"));
        break;
   }
    if (i == selection)
    {
      Serial.print(F("<<<"));
    }
    Serial.print(F("\n\r"));
  }
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
  return true;
}

void MenuExpCommand::print()
{
  if(selection <= 127)
  {
    Serial.print(F("CC"));
    Serial.print(selection,DEC);
  }
  else if (selection == 128)
  {
    Serial.print(F("PitchBend"));
  }
  Serial.print(F("\n\r"));
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
  switch (selection)
  {
    case 0:
      Serial.print(F("normal"));
      break;
    case 1:
      Serial.print(F("reverse"));
      break;
  }
  Serial.print(F("\n\r"));
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
  for (int i = 0; i< nbItems; i++)
  {
    switch (i)
    {
      case 0:
        Serial.print(F("EXP"));
        Serial.print(expNum, DEC);
        Serial.print(F(" Cmd"));
        break;
      case 1:
        Serial.print(F("EXP"));
        Serial.print(expNum, DEC);
        Serial.print(F(" Mode"));
        break;
    }
    if (i == selection)
    {
      Serial.print(F("<<<"));
    }
    Serial.print(F("\n\r"));
  }
}

//MenuSwSelect

//ctor
MenuSwSelect::MenuSwSelect(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  Preset* pt_preset)
  : MenuBase(pt_manager, pt_parent),
    fsConfig(pt_manager, this, this, pt_preset),
    expConfig(pt_manager, this, this, pt_preset),
    pt_preset(pt_preset){}

uint8_t MenuSwSelect::nbItems()
{
  if (pt_preset != NULL)
  {
    uint8_t sum =
      pt_preset->get_nbFsConfigs() +
      pt_preset->get_nbExpConfigs();
    return sum;
  }
  else
  {
    return 0;
  }
}

bool MenuSwSelect::next()
{
  bool res = false;
  if (this->selection < this->nbItems() -1)
  {
    this->selection++;
    res = true;
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
  return res;
}

bool MenuSwSelect::validate()
{
  bool res = false;
  uint8_t nbFs = pt_preset->get_nbFsConfigs();
  uint8_t nbExp = pt_preset->get_nbExpConfigs();
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
  return true;
}

void MenuSwSelect::print()
{
  if (pt_preset != NULL)
  {
    for (int i = 0; i< nbItems(); i++)
    {
      uint8_t nbFs = pt_preset->get_nbFsConfigs();
      uint8_t nbExp = pt_preset->get_nbExpConfigs();
      if (i < nbFs)
      {
        Serial.print(F("FS "));
        Serial.print(i, DEC);
      }
      else if (i < (nbFs + nbExp))
      {
        Serial.print(F("Exp "));
        Serial.print(i - nbFs, DEC);
      }
      if (i == selection)
      {
        Serial.print(F("<<<"));
      }
      Serial.print(F("\n\r"));
    }
  }
}

uint8_t MenuSwSelect::get_selectedFsNum()
{
  uint8_t nbFs = pt_preset->get_nbFsConfigs();
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
  uint8_t nbFs = pt_preset->get_nbFsConfigs();
  uint8_t nbExp = pt_preset->get_nbExpConfigs();
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
  
  for (int i = displayOffset; i< (displayOffset + 4); i++)
  {
    Serial.print(F("Preset "));
    Serial.print(i,DEC);
    if (i == selection)
    {
      Serial.print(F("<<<"));
    }
    Serial.print(F("\n\r"));
  }
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
  
  for (int i = displayOffset; i< (displayOffset + 4); i++)
  {
    Serial.print(F("Preset "));
    Serial.print(i,DEC);
    if (i == selection)
    {
      Serial.print(F("<<<"));
    }
    Serial.print(F("\n\r"));
  }
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
  for (int i = displayOffset; i< (displayOffset + 4) and i<nbItems; i++)
  {
    switch(i)
    {
      case 0:
        Serial.print(F("Midi chan"));
        break;
      case 1:
        Serial.print(F("Exp cal"));
        break;
    }
    if (i == selection)
    {
      Serial.print(F("<<<"));
    }
    Serial.print(F("\n\r"));
  }
}



//MenuMainConf

//ctor
MenuMainConf::MenuMainConf(
  MenuManager* pt_manager,
  MenuBase* pt_parent,
  Preset* pt_preset)
  : MenuBase(pt_manager,pt_parent),
    swSelect(pt_manager, this, pt_preset),
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
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
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
  for (int i = 0; i< nbItems; i++)
  {
    switch(i)
    {
      case 0:
        Serial.print(F("SW set"));
        break;
      case 1:
        Serial.print(F("Load Pres"));
        break;
      case 2:
        Serial.print(F("Save Pres"));
        break;
      case 3:
        Serial.print(F("Gen. set"));
        break;
      default:
        break;
    }
    if (selection == i)
    {
      Serial.print(F("<<<"));
    }
    Serial.print(F("\n\r"));
  }
}

