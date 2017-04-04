#include "menus.h"

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


extern MenuFolder mainConf;
extern MenuFolder swSelect;
extern MenuPresetLoad loadPreset;
extern MenuEnumSelect fswModeSelect;


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
  MenuFolder_Item(&fswModeSelect,"FS 0"),
  MenuFolder_Item(NULL,"FS 1"),
  MenuFolder_Item(NULL,"FS 2"),
  MenuFolder_Item(NULL,"FS 3")
};
MenuFolder swSelect(&manager,&mainConf,swSelect_items,4);


const char* fswModeSelect_items[]
{
  "Tog(on)",
  "Tog(off)",
  "Mom(on)",
  "Mom(off)",
  "Sing(on)",
  "Sing(off)"
};
MenuEnumSelect fswModeSelect(&manager,&swSelect,fswModeSelect_items,6);
/*
MenuFolder_Item loadPreset_items [] = 
{
  MenuFolder_Item(NULL,"USER 0"),
  MenuFolder_Item(NULL,"USER 1"),
  MenuFolder_Item(NULL,"USER 2"),
  MenuFolder_Item(NULL,"USER 3")
};
MenuFolder loadPreset(&manager,&mainConf,loadPreset_items,4);
*/
MenuPresetLoad loadPreset(&manager,&mainConf, 129);

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
    //Serial.print(mainConf.selection,DEC);
  }
}
