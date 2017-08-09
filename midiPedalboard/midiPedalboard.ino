#include "menus.h"
#include "footswitch.h"
#include "preset.h"
#include <MIDIUSB.h>

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


Preset preset;

uint8_t fsValue[4];//on off, but not the raw digitalRead() value
int16_t expValue[1];//

uint8_t prec_fsRawValues[4];

extern MenuManager manager;

MenuMainConf mainConf(&manager,NULL,&preset);
MenuManager manager (&mainConf);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ROTARY_A, INPUT_PULLUP);
  pinMode(ROTARY_B, INPUT_PULLUP);
  pinMode(BUTTON_OK, INPUT_PULLUP);
  pinMode(BUTTON_CANCEL, INPUT_PULLUP);

  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);

  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
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
  //footswitch
  uint8_t fsRawValues[4];
  fsRawValues[0] = digitalRead(9);
  fsRawValues[1] = digitalRead(10);
  fsRawValues[2] = digitalRead(11);
  fsRawValues[3] = digitalRead(12);

  for(uint8_t i = 0; i < 4; i++)
  {
    uint8_t fsMode = preset.get_fsMode(i);
    uint8_t fsCommand = preset.get_fsCommand(i);
    switch(fsMode)
    {
      case 0:
      case 1:
        if((prec_fsRawValues[i] == HIGH) and (fsRawValues[i] == LOW))
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
        if((prec_fsRawValues[i] == HIGH) and (fsRawValues[i] == LOW))
        {
          fsValue[i] = 127;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        else if((prec_fsRawValues[i] == LOW) and (fsRawValues[i] == HIGH))
        {
          fsValue[i] = 0;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        break;
      case 3:
        if((prec_fsRawValues[i] == HIGH) and (fsRawValues[i] == LOW))
        {
          fsValue[i] = 0;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        else if((prec_fsRawValues[i] == LOW) and (fsRawValues[i] == HIGH))
        {
          fsValue[i] = 127;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        break;
      case 4:
        if((prec_fsRawValues[i] == HIGH) and (fsRawValues[i] == LOW))
        {
          fsValue[i] = 127;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
        break;
      case 5:
        if((prec_fsRawValues[i] == HIGH) and (fsRawValues[i] == LOW))
        {
          fsValue[i] = 0;
          //send midi CC throught USB
          midiEventPacket_t event = {0x0B,0xB0|0x00,fsCommand,fsValue[i]};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();
        }
    }
    prec_fsRawValues[i]=fsRawValues[i];
  }

  digitalWrite(A0,fsValue[0]);
  digitalWrite(A1,fsValue[1]);
  digitalWrite(A2,fsValue[2]);
  digitalWrite(A3,fsValue[3]);
}
