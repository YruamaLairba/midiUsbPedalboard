#include "setup.h"
#include "menu_system.h"
#include "footswitch.h"
#include "exp_pedal.h"
#include "global_setting.h"
#include "preset.h"
#include "display.h"
#include "rotary_encoder.h"
#include "warnings.h"
#include "push_button.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

//fooswitch
Footswitch fs[nbFs];
ExpPedal expPedal[nbExp];
GlobalSetting global_setting;
Preset preset(fs, nbFs, expPedal, nbExp);

unsigned long last_micros;

unsigned long debug_last_micros;

MenuSystem menu_system;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  global_setting.init();

  //footswitch class initialisation
  for(uint8_t i=0; i<nbFs; i++)
  {
    fs[i].setup(fsPins[i], fsLedPins[i], &global_setting);
  }

  //expPedal class initialisation
  for(uint8_t i=0; i<nbExp; i++)
  {
    expPedal[i].setup(expPins[i], &global_setting);
  }

  preset.init();

  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE,BLACK);
  display.setTextWrap(0);
  menu_system.init();

}

void loop() {
  // put your main code here, to run repeatedly:
  menu_system.process();
  for(uint8_t i = 0; i < nbFs; i++)
  {
    fs[i].process();
  }
#if 1
  for(uint8_t i = 0; i < nbExp; i++)
  {
    expPedal[i].process();
  }
#endif
}
