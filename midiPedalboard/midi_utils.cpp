#include "midi_utils.h"

void midi_send_cvm(uint8_t status, uint8_t data0, uint8_t data1)
{
  uint8_t usb_header= (status & 0xF0) >> 4;
  Serial1.begin(31250);
  Serial1.write(status);
  Serial1.write(data0);
  Serial1.write(data1);
  midiEventPacket_t event = {
    usb_header,
    status,
    data0,
    data1,
  };
  MidiUSB.sendMIDI(event);
  Serial1.flush();
  Serial1.end();
  MidiUSB.flush();
}

void midi_send_mmc_cmd(uint8_t cmd)
{
  Serial1.begin(31250);
  Serial1.write(0xF0);
  Serial1.write(0x7F);
  Serial1.write(0x7F);
  Serial1.write(0x06);
  Serial1.write(cmd);
  Serial1.write(0xF7);
  Serial1.flush();
  Serial1.end();
  midiEventPacket_t events[2] =
  {
    {0x04,0xF0,0x7F,0x7F},
    {0x04,0x06,cmd,0xF7},
  };
  MidiUSB.sendMIDI(events[0]);
  MidiUSB.sendMIDI(events[1]);
  MidiUSB.flush();
}

