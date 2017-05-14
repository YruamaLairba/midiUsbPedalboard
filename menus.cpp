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

//MenuFolder
void MenuFolder::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuFolder::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuFolder::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuFolder::validate()
{
  bool res = false;
  MenuBase* pt_item = items[selection].get_item();
  if(pt_item != NULL)
  {
    pt_item->activate();
    res = true;
  }
  return res;
}

bool MenuFolder::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuFolder::reset()
{
  selection = 0;
  return true;
}

void MenuFolder::print()
{
  
  for (int i = 0; i< nbItems; i++)
  {
    Serial.print(items[i].get_label());
    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}

//MenuSwSelect

bool MenuSwSelect::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
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
  if(selection < 4)
  {
    swConfig->set_swToConfig(selection);
    swConfig->activate();
    res = true;
  }
  else if (selection < 5)
  {
    expConfig->set_swToConfig(0);
    expConfig->activate();
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
  
  for (int i = 0; i< nbItems; i++)
  {
    if (i<4)
    {
      Serial.print("FS ");
      Serial.print(i,DEC);
    }
    else if (i == 4)
    {
      Serial.print("Exp");
    }


    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}

//MenuSwConfig
bool MenuSwConfig::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuSwConfig::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuSwConfig::validate()
{
  bool res = false;
  return res;
}

bool MenuSwConfig::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuSwConfig::reset()
{
  selection = 0;
  return true;
}

void MenuSwConfig::print()
{
  
  for (int i = 0; i< nbItems; i++)
  {
    switch (i)
    {
      case 0: Serial.print("FS Cmd");break;
      case 1: Serial.print("FS Mode");break;
    }
    
    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}
//
//MenuExpConfig
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
  bool res = false;
  return res;
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
  
  for (int i = 0; i< nbItems; i++)
  {
    switch (i)
    {
      case 0: Serial.print("EXP Cmd");break;
      case 1: Serial.print("EXP Mode");break;
    }

    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}


//MenuPresetLoad

//ctor
MenuPresetLoad::MenuPresetLoad(MenuManager* pt_manager, MenuBase* pt_parent)
  : MenuBase(pt_manager, pt_parent),
    nbPreset(128)
    {}

void MenuPresetLoad::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuPresetLoad::next()
{
  bool res = false;
  if (this->selection < this->nbPreset -1)
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

#warning "this is only a prototype"
bool MenuPresetLoad::validate()
{
  Serial.print("Preset ");
  Serial.print(selection,DEC);
  Serial.print(" loaded\n\r");
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
    Serial.print("Preset ");
    Serial.print(i,DEC);
    if (i == selection)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}

//MenuMainConf

//ctor
#warning :"unfinished"
MenuMainConf::MenuMainConf(MenuManager* pt_manager, MenuBase* pt_parent)
  : MenuBase(pt_manager,pt_parent),
    //swSelect(pt_manager, this),
    presetLoad(pt_manager, this),
    //presetSave(pt_manager, this),
    //generalSetting(pt_manager, this)
    nbItems(4)
    {}

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

#warning: "not finished"
bool MenuMainConf::validate()
{
  bool res = false;
  switch (selection)
  {
    case 0:
      //swSelect.activate();
      res=true;
      break;
    case 1:
      presetLoad.activate();
      res=true;
      break;
    case 2:
      //presetSave.activate();
      res=true;
      break;
    case 3:
      //generalSetting.activate();
      res=true;
      break;
  return res;
  }
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
        Serial.print("SW set");
        break;
      case 1:
        Serial.print("Load Pres");
        break;
      case 2:
        Serial.print("Save Pres");
        break;
      case 3:
        Serial.print("Gen. set");
        break;
      default:
        break;
    }
    if (selection == i)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}


//MenuEnumSelect
void MenuEnumSelect::activate()
{
  this->reset();
  manager->set_active(this);
}

bool MenuEnumSelect::next()
{
  bool res = false;
  if (this->selection < this->nbItems -1)
  {
    this->selection++;
    res = true;
  }
  return res;
}

bool MenuEnumSelect::prev()
{
  bool res = false;
  if (this->selection > 0)
  {
    this->selection--;
    res = true;
  }
  return res;
}

bool MenuEnumSelect::validate()
{
  //TODO
  return true;
}

bool MenuEnumSelect::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->set_active(parent);
    res = true;
  }
  return res;
}

bool MenuEnumSelect::reset()
{
  selection = 0;
  return true;
}

void MenuEnumSelect::print()
{
  Serial.print(items[selection]);
  Serial.print("\n\r");
}



