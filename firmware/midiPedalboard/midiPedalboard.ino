#include "setup.h"
#include "menu_system.h"
#include "controller_system.h"
#include "display.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

#ifdef DEBUG
unsigned long loop_last_micros;
#endif

ControllerSystem controller_system;
MenuSystem menu_system(&controller_system);

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  controller_system.init();

  display.begin(&Adafruit128x64, displayCs, displayDc, displayReset);
  display.clear();
  display.setFont(Adafruit5x7); 
  display.set2X();
  display.setInvertMode(true);
  menu_system.init();

}

void loop() {
#ifdef DEBUG
  unsigned long int menu_system_time = micros();
#endif
  menu_system.process();
#ifdef DEBUG
  unsigned long int menu_system_time2 = micros();
  unsigned int long diff = menu_system_time2 - menu_system_time;
  if(diff >1000)
  {
    Serial.print("menu system delay : ");
    Serial.println(diff);
  }
#endif

#ifdef DEBUG
  unsigned long int controller_system_time = micros();
#endif
  controller_system.process();
#ifdef DEBUG
  unsigned long int controller_system_time2 = micros();
  unsigned long int diff2 = controller_system_time2 - controller_system_time;
  if(diff2>1000)
  {
    Serial.print("controller system delay : ");
    Serial.println(diff2);
  }
#endif
#ifdef DEBUG
  unsigned long int loop_micros = micros();
  unsigned long int loop_time = loop_micros - loop_last_micros;
  loop_last_micros = loop_micros;
  if(loop_time>1000)
  {
    Serial.print("loop duration : ");
    Serial.println(loop_time);
  }
#endif

}
