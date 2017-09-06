#include "setup.h"
#include "menus.h"
#include "footswitch.h"
#include "preset.h"
#include <MIDIUSB.h>
#include "display.h"

//rotary coder
uint8_t prec_rot_a;
uint8_t prec_rot_b;
uint8_t cur_rot_a;
uint8_t cur_rot_b;
uint8_t rot_a_acc;
uint8_t rot_b_acc;

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

//expression pedal value
int16_t expValue[nbExp];

unsigned long last_micros;

unsigned long debug_last_micros;

Preset preset;
extern MenuManager manager;

MenuMainConf mainConf(&manager,NULL,&preset);
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
  pinMode(rotaryPinA, INPUT_PULLUP);
  pinMode(rotaryPinB, INPUT_PULLUP);
  pinMode(buttonOkPin, INPUT_PULLUP);
  pinMode(buttonCancelPin, INPUT_PULLUP);

  //footswitch and leds pins
  for(uint8_t i=0; i<nbFs; i++)
  {
    pinMode(fsPins[i],INPUT_PULLUP);
    pinMode(fsLedPins[i],OUTPUT);
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
    filterButton(digitalRead(rotaryPinA), 20, &rot_a_acc, &cur_rot_a);
    filterButton(digitalRead(rotaryPinB), 20, &rot_b_acc, &cur_rot_b);

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

  uint8_t curtemp = cur_rot_a | cur_rot_b << 1 | prec_rot_a << 2 |
    prec_rot_b << 3;
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

  //footswitch
  unsigned long debug_start_micros = micros();
  for(uint8_t i = 0; i < nbFs; i++)
  {
    uint8_t fsMode = preset.get_fsMode(i);
    uint8_t fsCommand = preset.get_fsCommand(i);
    switch(fsMode)
    {
      case 0:
      case 1:
        if((prec_fsRawValues[i] == HIGH) and (cur_fsRawValues[i] == LOW))
        {
          if (fsValue[i] == 0)
          {
            fsValue[i]=127;
          }
          else
          {
            fsValue[i]=0;
          }
          if(fsCommand < 128)
          {
            //send midi CC throught USB
            midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
            MidiUSB.sendMIDI(event);
            MidiUSB.flush();
          }
        }
        break;
      case 2:
        if((prec_fsRawValues[i] == HIGH) and (cur_fsRawValues[i] == LOW))
        {
          fsValue[i] = 127;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        else if((prec_fsRawValues[i] == LOW) and (cur_fsRawValues[i] == HIGH))
        {
          fsValue[i] = 0;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        break;
      case 3:
        if((prec_fsRawValues[i] == HIGH) and (cur_fsRawValues[i] == LOW))
        {
          fsValue[i] = 0;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        else if((prec_fsRawValues[i] == LOW) and (cur_fsRawValues[i] == HIGH))
        {
          fsValue[i] = 127;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        break;
      case 4:
        if((prec_fsRawValues[i] == HIGH) and (cur_fsRawValues[i] == LOW))
        {
          fsValue[i] = 127;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        break;
      case 5:
        if((prec_fsRawValues[i] == HIGH) and (cur_fsRawValues[i] == LOW))
        {
          fsValue[i] = 0;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
    }
    prec_fsRawValues[i]=cur_fsRawValues[i];
    digitalWrite(fsLedPins[i],fsValue[i]);
  }
  unsigned long debug_end_micros = micros();
  unsigned long debug_duration = debug_end_micros - debug_start_micros;
  if (debug_duration > 1000)
  {
    Serial.print("debug_duration : ");
    Serial.print(debug_duration,DEC);
    Serial.print("\n\r");
  }
}
