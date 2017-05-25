#ifndef MENUS_H
#define MENUS_H

#include <stdint.h>
#include <Arduino.h>// for Serial

#include "preset.h"


class MenuBase;

class MenuManager
{
  private:
    MenuBase * const pt_root ;
    MenuBase * pt_current ;
  public:
    MenuManager(MenuBase* root):pt_root(root),pt_current(root){}

    void set_active(MenuBase* activated);

    bool next();
    bool prev();
    bool validate();
    bool cancel();
    void print();
};


class  MenuBase
{
  protected:
    MenuManager * const manager;
    MenuBase * const parent ;

    uint8_t selection;
    //int8_t selectionMax;


  public:
    MenuBase(MenuManager* manager, MenuBase* parent):
    manager(manager),
    parent(parent)
    {}
    virtual void activate();

    virtual bool next() = 0;
    virtual bool prev() = 0;
    virtual bool validate() = 0;
    virtual bool cancel() = 0;
    virtual bool reset() = 0;
    virtual void print() = 0;
};


//menu to select command associated to a footswitch
class MenuFsCommand : public MenuBase
{
  private:
    static const uint8_t selectionMax = 127;
    Preset* pt_preset;
  public:
    MenuFsCommand(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};

//menu to select mode of a footswitch
class MenuFsMode : public MenuBase
{
  private:
    static const uint8_t selectionMax = 5;
    Preset* pt_preset;
  public:
    MenuFsMode(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};

//menu root for Footswitch configuration
class MenuFsConfig : public MenuBase
{
  private:
    static const uint8_t nbItems = 2;
    MenuFsCommand menuFsCommand;
    MenuFsMode menuFsMode;
    Preset* pt_preset;
    //<a variable that represent footswitch that we modify>
  public:
    MenuFsConfig(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

    //void set_swToConfig(uint8_t swNumber){this->selectedSw = swNumber;};
};

//menu to select command associated to an expression pedal
class MenuExpCommand : public MenuBase
{
  private:
    static const uint8_t selectionMax = 128;
    Preset* pt_preset;
  public:
    MenuExpCommand(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};

//menu to select mode of a expression pedal
class MenuExpMode : public MenuBase
{
  private:
    static const uint8_t selectionMax = 1;
    Preset* pt_preset;
  public:
    MenuExpMode(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};

class MenuExpConfig : public MenuBase
{
  private:
    static const uint8_t nbItems = 2;
    MenuExpCommand menuExpCommand;
    MenuExpMode menuExpMode;
    Preset* pt_preset;
  public:
    MenuExpConfig(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);
    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

    //void set_swToConfig(uint8_t swNumber){this->selectedSw = swNumber;};
};



//the menu to select a fooswitch or an expresion pedal for config
class MenuSwSelect : public MenuBase
{
  private:
    MenuFsConfig fsConfig;
    MenuExpConfig expConfig;
    Preset* pt_preset;
    uint8_t nbItems();

  public:
    /*
    MenuSwSelect(
      MenuManager* manager,
      MenuBase* parent,
      MenuFsConfig* fsConfig,
      MenuExpConfig* expConfig)
      : MenuBase(manager,parent),
        fsConfig(fsConfig),
        expConfig(expConfig){}
    */
    MenuSwSelect(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);
    //virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

    uint8_t get_selectedFsNum();
    uint8_t get_selectedExpNum();
};

class MenuPresetLoad : public MenuBase
{
  private:
    //int8_t userPresetSelect;
    //int8_t factoryPresetSelect;

    //int8_t nbUserPreset;
    //int8_t nbFactoryPreset;
    uint8_t displayOffset;

    uint8_t nbPreset;
  public:
    //MenuPresetLoad(MenuManager* manager, MenuBase* parent, int8_t nbUserPreset,int8_t nbFactoryPreset):
    //MenuBase(manager,parent), //if nbItems is x, selectionMax is x-1
    //nbUserPreset(nbUserPreset),
    //nbFactoryPreset(nbFactoryPreset)
    MenuPresetLoad(MenuManager* pt_manager, MenuBase* pt_parent);

    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();
};

class MenuPresetSave : public MenuBase
{
  private:
    uint8_t displayOffset;
    uint8_t nbPreset;
  public:
    //MenuPresetSave(MenuManager* manager, MenuBase* parent, int8_t nbUserPreset,int8_t nbFactoryPreset):
    //MenuBase(manager,parent), //if nbItems is x, selectionMax is x-1
    //nbUserPreset(nbUserPreset),
    //nbFactoryPreset(nbFactoryPreset)
    MenuPresetSave(MenuManager* pt_manager, MenuBase* pt_parent);

    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();
};

#warning "MenuGeneralSetting: need submenu"
class MenuGeneralSetting : public MenuBase
{
  private:
    uint8_t displayOffset;
    int8_t nbItems;

  public:
    MenuGeneralSetting(MenuManager* pt_manager, MenuBase* pt_parent);

    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();
};


//menu mainConf
class MenuMainConf : public MenuBase
{
  private:
    MenuSwSelect swSelect;
    MenuPresetLoad presetLoad;
    MenuPresetSave presetSave;
    MenuGeneralSetting generalSetting;
    static const int8_t nbItems = 4;

  public:
    MenuMainConf(
      MenuManager* pt_manager,
      MenuBase* pt_parent,
      Preset* pt_preset);

    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};

#endif //MENUS_H
