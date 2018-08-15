#include "setup.h"
#include "menus.h"
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

//rotary coder
RotaryEncoder rot(rotaryPinA,rotaryPinB);

//fooswitch
Footswitch fs[nbFs];
ExpPedal expPedal[nbExp];
GlobalSetting global_setting;
Preset preset(fs, nbFs, expPedal, nbExp);

//button ok
PushButton button_ok(buttonOkPin);
uint8_t prec_button_ok;
uint8_t cur_button_ok;
uint8_t button_ok_acc;//used for debounce filter

//button cancel
PushButton button_cancel(buttonCancelPin);
uint8_t prec_button_cancel;
uint8_t cur_button_cancel;
uint8_t button_cancel_acc;

unsigned long last_micros;

unsigned long debug_last_micros;


extern MenuManager manager;

MenuMainConf mainConf(&manager,NULL,&global_setting,&preset,fs,nbFs);
MenuManager manager (&mainConf);

//function to avoid bounce and glitch issue on input
void filterButton(
  uint8_t raw_input,
  uint8_t treshold,
  uint8_t *acc,
  uint8_t *filtered_input)
{
  if ((raw_input == HIGH) and  (*acc < treshold))
  {
    (*acc)++;
    if (*acc >= treshold) *filtered_input = HIGH;
  }
  else if ((raw_input == LOW) and  (*acc > 0))
  {
    (*acc)--;
    if (*acc <= 0) *filtered_input = LOW;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonOkPin, INPUT_PULLUP);
  pinMode(buttonCancelPin, INPUT_PULLUP);

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
}

void loop() {
  // put your main code here, to run repeatedly:
  bool refresh=false;

  //debounce filtering
  unsigned current_micros = micros();
  if ((current_micros - last_micros) > 100)
  {
    filterButton(digitalRead(buttonOkPin), 50, &button_ok_acc, &cur_button_ok);
    filterButton(digitalRead(buttonCancelPin), 50, &button_cancel_acc,
                 &cur_button_cancel);
    last_micros = current_micros;
  }

  int tmp = rot.read();
  if(tmp < 0) refresh=manager.prev();
  else if(tmp > 0) refresh=manager.next();

  //validate
  if (button_ok.read()== PushButtonVal::pressed)
  {
    refresh = manager.validate(); 
  }
  prec_button_ok = cur_button_ok;

  //cancel
  if (button_cancel.read()== PushButtonVal::pressed)
  {
    refresh = manager.cancel(); 
  }
  prec_button_cancel = cur_button_cancel;

  if (refresh)
  {
    manager.print();
  }

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
