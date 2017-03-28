#define ROTARY_A 2
#define ROTARY_B 3

uint8_t prec_rot_a;
uint8_t prec_rot_b;

//button ok
#define BUTTON_OK 7
uint8_t prec_button_ok;

//button cancel
#define BUTTON_CANCEL 8
uint8_t prec_button_cancel;

class MenuBase;


class MenuManager
{
  public:
    MenuBase * const pt_root ;
    MenuBase * pt_current ;
  public:
    MenuManager(MenuBase* root):pt_root(root),pt_current(root){}
 
    bool next();
    bool prev();
    bool validate();
    bool cancel();
    void print();
};

class  MenuBase
{
  public:
    MenuManager * const manager;
    MenuBase * const parent ;

  public:
    MenuBase(MenuManager* manager, MenuBase* parent):
    manager(manager),
    parent(parent)
    {}
    virtual void activate() = 0;
      
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
  public:
    MenuBase* item;
    char * label;
  public: 
    MenuFolder_Item(MenuBase* item,char * label):
    item(item),
    label(label)
    {}

    MenuBase* get_item(){return item;}
    char* get_label(){return label;}
};

//a menu that contain submenu
class MenuFolder : public MenuBase
{
  public:
    MenuFolder_Item * items;
    int8_t nbItems;
    int8_t selectedItem;
  
  public:
    MenuFolder(MenuManager* manager, MenuBase* parent, MenuFolder_Item * items,int8_t nbItems):
    MenuBase(manager,parent),
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

void MenuFolder::activate()
{
  this->reset();
  manager->pt_current = this;
}

bool MenuFolder::next()
{
  bool res = false;
  if (this->selectedItem < this->nbItems - 1)
  {
    this->selectedItem++;
    res = true;
  }
  return res;
}

bool MenuFolder::prev()
{
  bool res = false;
  if (this->selectedItem > 0)
  {
    this->selectedItem--;
    res = true;
  }
  return res;
}

bool MenuFolder::validate()
{
  bool res = false;
  if(items[selectedItem].item != NULL)
  {
    items[selectedItem].item->activate();
    res = true;
  }
  return res;
}

bool MenuFolder::cancel()
{
  bool res = false;
  if(parent != NULL)
  {
    manager->pt_current = parent;
    res = true;
  }
  return res;
}

bool MenuFolder::reset()
{
  selectedItem = 0;
  return true;
}

void MenuFolder::print()
{
  
  for (int i = 0; i< nbItems; i++)
  {
    Serial.print(items[i].label);
    if (i == selectedItem)
    {
      Serial.print("<<<");
    }
    Serial.print("\n\r");
  }
}

//typedef struct MenuManager MenuManager;


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


extern MenuFolder mainConf;
extern MenuFolder swSelect;
extern MenuFolder loadPreset;


extern MenuManager manager;


MenuFolder_Item mainConf_items [] = 
{
  MenuFolder_Item(&swSelect,"SW set"),
  MenuFolder_Item(&loadPreset,"Load pres"),
  MenuFolder_Item(NULL,"Save pres"),
  MenuFolder_Item(NULL,"Gen. set")
};
MenuFolder mainConf(&manager,NULL,mainConf_items,4);

MenuFolder_Item swSelect_items [] = 
{
  MenuFolder_Item(NULL,"FS 0"),
  MenuFolder_Item(NULL,"FS 1"),
  MenuFolder_Item(NULL,"FS 2"),
  MenuFolder_Item(NULL,"FS 3")
};
MenuFolder swSelect(&manager,&mainConf,swSelect_items,4);

MenuFolder_Item loadPreset_items [] = 
{
  MenuFolder_Item(NULL,"USER 0"),
  MenuFolder_Item(NULL,"USER 1"),
  MenuFolder_Item(NULL,"USER 2"),
  MenuFolder_Item(NULL,"USER 3")
};
MenuFolder loadPreset(&manager,&mainConf,loadPreset_items,4);


MenuManager manager (&mainConf);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ROTARY_A, INPUT_PULLUP);
  pinMode(ROTARY_B, INPUT_PULLUP);
  pinMode(BUTTON_OK, INPUT_PULLUP);
  pinMode(BUTTON_CANCEL, INPUT_PULLUP);  
}

void loop() {
  // put your main code here, to run repeatedly:
  bool refresh=false;
  //rotary
  uint8_t cur_rot_a = digitalRead(ROTARY_A);
  uint8_t cur_rot_b = digitalRead(ROTARY_B);

  uint8_t curtemp = cur_rot_a | cur_rot_b << 1 | prec_rot_a << 2 | prec_rot_b << 3;
  //management of half cycle per indent encoder
  if (curtemp == 0b00000001 ||
      //curtemp == 0b00000111 ||
      //curtemp == 0b00001000 ||
      curtemp == 0b00001110)
  {
    refresh = manager.next();
  }
  else if (curtemp == 0b00000010 ||
           //curtemp == 0b00000100 ||
           //curtemp == 0b00001011 ||
           curtemp == 0b00001101)
  {
    refresh = manager.prev();
  }
  prec_rot_a = cur_rot_a;
  prec_rot_b = cur_rot_b;

  //validate
  uint8_t cur_button_ok = digitalRead(BUTTON_OK);
  if (prec_button_ok == HIGH and cur_button_ok == LOW)
  {
    refresh = manager.validate(); 
  }
  prec_button_ok = cur_button_ok;

  //cancel
  uint8_t cur_button_cancel = digitalRead(BUTTON_CANCEL);
  if (prec_button_cancel == HIGH and cur_button_cancel == LOW)
  {
    refresh = manager.cancel(); 
  }
  prec_button_cancel = cur_button_cancel;
  
  if (refresh)
  {
    manager.print();
    /*
    Menu * const* tmp = mainConf.items;
    Serial.print((int)&mainConf,HEX);Serial.print("\n\r");
    Serial.print((int)*(mainConf.items),HEX);Serial.print("\n\r");
    Serial.print((int)(mainConf.items),HEX);Serial.print("\n\r");
    Serial.print((int)tmp[0],HEX);Serial.print("\n\r");
    Serial.print((int)mainConf_items,HEX);Serial.print("\n\r");
    Serial.print((int)*(mainConf_items),HEX);Serial.print("\n\r");
    Serial.print((int)&(mainConf_items),HEX);Serial.print("\n\r");
    */
    //mainConf.print(&mainConf);
    //Serial.print(mainConf.selectedItem,DEC);
  }
}
