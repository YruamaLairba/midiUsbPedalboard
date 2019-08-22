#ifndef MIDI_UTILS_H
#define MIDI_UTILS_H

#include "warnings.h"
DIAGNOSTIC_IGNORE_ALL
#include <MIDIUSB.h>
DIAGNOSTIC_POP


//some useful things to handle midi

//mapping beetween some 'MIDI Machine Control' command bytes and theire name
enum MMC_CMD : uint8_t
{
  STOP=0x01,
  PLAY=0x02,
  FAST_FORWARD=0x04,
  REWIND=0x05,
  RECORD_STROBE=0x06,
  RECORD_EXIT=0x07,
  PAUSE=0x09
};


//send a 'channel voice message' on USB and on Serial1
void midi_send_cvm(uint8_t status, uint8_t data0, uint8_t data1=0);

//send a 'MIDI Machine Control' on USB and on Serial1
void midi_send_mmc_cmd(uint8_t cmd);


#endif //MIDI_UTILS_H
