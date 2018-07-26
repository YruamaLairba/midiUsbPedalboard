#include <MIDIUSB.h>
#include "setup.h"
#include "menus.h"
#include "footswitch.h"
#include "expPedal.h"
#include "global_setting.h"
#include "preset.h"
#include "display.h"
#include "rotary_encoder.h"

//rotary coder
RotaryEncoder rot(rotaryPinA,rotaryPinB);

//fooswitch
Footswitch fs[nbFs];
ExpPedal expPedal[nbExp];
GlobalSetting global_setting;
Preset preset(fs, nbFs, expPedal, nbExp);

//button ok
uint8_t prec_button_ok;
uint8_t cur_button_ok;
uint8_t button_ok_acc;//used for debounce filter

//button cancel
uint8_t prec_button_cancel;
uint8_t cur_button_cancel;
uint8_t button_cancel_acc;

//footswitchs physical value
uint8_t cur_fsRawValues[nbFs];
uint8_t prec_fsRawValues[nbFs];
uint8_t fsRawValues_acc[nbFs];

//footswitchs software value
uint8_t fsValue[nbFs];//on off, but not the raw digitalRead() value

unsigned long leds_millis[nbFs]; //used to blink led

//expression pedal value
int16_t expValue[nbExp];

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
  preset.init();

  //footswitch class initialisation
  for(uint8_t i=0; i<nbFs; i++)
  {
    fs[i].setup(fsPins[i], fsLedPins[i]);
  }

  //expPedal class initialisation
  for(uint8_t i=0; i<nbExp; i++)
  {
    expPedal[i].setup(expPins[i]);
  }

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

    //read footswitch input
    for(uint8_t i=0; i<nbFs; i++)
    {
    filterButton(digitalRead(fsPins[i]), 50, &fsRawValues_acc[i],
        &cur_fsRawValues[i]);
    }

    last_micros = current_micros;
  }

  int tmp = rot.read();
  if(tmp < 0) refresh=manager.prev();
  else if(tmp > 0) refresh=manager.next();

  //validate
  if (prec_button_ok == HIGH and cur_button_ok == LOW)
  {
    refresh = manager.validate(); 
  }
  prec_button_ok = cur_button_ok;

  //cancel
  if (prec_button_cancel == HIGH and cur_button_cancel == LOW)
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
    int8_t val = fs[i].read();
    if (val >= 0)
    {
      midiEventPacket_t event = {
        0x0B,
        0xB0|global_setting.get_midi_channel(),
        fs[i].get_command(),
        val
      };
      MidiUSB.sendMIDI(event);
      MidiUSB.flush();
    }
  }

#if 1
  for(uint8_t i = 0; i < nbExp; i++)
  {
    int16_t val = expPedal[i].read();
    if (val >= 0)
    {
      int8_t val2 = val/8;
#ifdef DEBUG
      Serial.println(val,DEC);
#endif
      midiEventPacket_t event = {
        0x0B,
        0xB0|global_setting.get_midi_channel(),
        expPedal[i].get_command(),
        val2
      };
      MidiUSB.sendMIDI(event);
      MidiUSB.flush();
    }
  }
#endif
}
