#include "setup.h"
#include "menu_system.h"
#include "controller_system.h"
#include "display.h"
#include "warnings.h"

DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP

unsigned long last_micros;
unsigned long debug_last_micros;

ControllerSystem controller_system;
MenuSystem menu_system(&controller_system);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(31250);//physical serial configured for midi
  controller_system.init();

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE,BLACK);
  display.setTextWrap(0);
  menu_system.init();

}

void loop() {
  // put your main code here, to run repeatedly:
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

}
