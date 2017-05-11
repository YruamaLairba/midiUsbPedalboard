#ifndef MENUS_H
#define MENUS_H

#include <stdint.h>
#include <Arduino.h>// for Serial


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


// class associating a label an a menu element
class MenuFolder_Item
{
  private:
    MenuBase* item;
    const char * label;
  public:
    MenuFolder_Item(MenuBase* item, const char * label):
    item(item),
    label(label)
    {}

    MenuBase* get_item(){return item;}
    const char* get_label(){return label;}
};


//a menu that contain submenu
class MenuFolder : public MenuBase
{
  private:
    MenuFolder_Item * items;
    int8_t nbItems;
  public:
    MenuFolder(MenuManager* manager, MenuBase* parent, MenuFolder_Item * items,int8_t nbItems):
    MenuBase(manager,parent), //if nbItems is x, selectionMax is x-1
    items(items),
    nbItems(nbItems)
    {}
    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};

//the menu to select a fooswitch or an expresion pedal
class MenuSwConfig; //forward declaration
class MenuExpConfig; //forward declaration

class MenuSwSelect : public MenuBase
{
  private:
     const int8_t nbItems = 5;
    #warning: "fix me"
    MenuSwConfig* swConfig;
    MenuExpConfig* expConfig;
    //MenuBase* expswConfig;

  public:
    MenuSwSelect(MenuManager* manager, MenuBase* parent,MenuSwConfig* swConfig,MenuExpConfig* expConfig):
    MenuBase(manager,parent),
    swConfig(swConfig),
    expConfig(expConfig)
    {}

    //virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();  
};



class MenuSwConfig : public MenuBase
{
  private:
    const uint8_t nbItems = 2;
    uint8_t selectedSw;
    #warning: "fix me"
    //MenuBase* fsMode;
    //MenuBase* fsCommand;
  public:
    MenuSwConfig(MenuManager* manager, MenuBase* parent):
    MenuBase(manager,parent)
    {}

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

    void set_swToConfig(uint8_t swNumber){this->selectedSw = swNumber;};
};


class MenuExpConfig : public MenuBase
{
  private:
    const uint8_t nbItems = 2;
    uint8_t selectedSw;
    #warning: "fix me"
    //MenuBase* fsMode;
    //MenuBase* fsCommand;
  public:
    MenuExpConfig(MenuManager* manager, MenuBase* parent):
    MenuBase(manager,parent)
    {}

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

    void set_swToConfig(uint8_t swNumber){this->selectedSw = swNumber;};
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
    MenuPresetLoad(MenuManager* manager, MenuBase* parent, int8_t nbPreset):
    MenuBase(manager,parent),
    nbPreset(nbPreset) 
    {}

    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();
};

class MenuEnumSelect : public MenuBase
{
  private:
    const char** items;
    uint8_t nbItems;
  public:
    MenuEnumSelect(MenuManager* manager, MenuBase* parent, const char** items, uint8_t nbItems):
    MenuBase(manager,parent),items(items),nbItems(nbItems){}

    virtual void activate();

    virtual bool next();
    virtual bool prev();
    virtual bool validate();
    virtual bool cancel();
    virtual bool reset();
    virtual void print();

};



#endif //MENUS_H
