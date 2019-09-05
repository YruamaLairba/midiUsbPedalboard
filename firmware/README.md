# midiPedalboard

This is the firmware for a configurable midi USB foot controller with 4
footswitches and 1 expression pedal. The project is build around the arduino
micro board.

## License

I release this code under GPL V3 licence, the full text is in LICENSE.txt

## Building the firmware

1. Change the bootloader

When you connect the USB port, the original bootloader write 2 byte in an
unsafe way in the middle of memory, and may corrupt some data. One solution is
to use [Hoodloader 2](https://github.com/NicoHood/HoodLoader2).

2. Get additional librairies

   All following libraries can be installed from the librairies manager :

   * MIDIUSB
   * SSD1306Ascii by Bill Greiman

3. Open and build midiPedalboard.ino, compile the project and load it into the
board.

## Component and pin layout

### Component for the configuration interface
* a 128x64 SSD1306 screen, SPI version,
* a rotary encoder and 2 condensators for debouncing it. Connect condensators
beetween ground and each output of the rotary encoder. Mine are 100nf but the
exact value is'nt very important.
* 2 momentary push buttons, one for "ok", the other for "cancel"

### Foot control part
* 4 momentary (normally open) switch. I recommend footswitch with soft touch.
* 4 leds. They are used to show footswitch status.
* 4 resistances, put each of them in serie with led to limits their current
* An expression pedal ;). you may also need a female jack connector. a switched
connector is better because it can avoid "floating input" when no expression
pedal is connected.

### Pin layout
Most of pins are in setup.h and can be changed. Exception are :

* MOSI of the arduino, connected to the data input of the SSD1306 screen
* SCK of the arduino, connected to the clock input of the SSD1306 screen
* pin 0/Rx of the arduino, not yet used but reserved for midi reception
* pin 1/Tx of the arduino, used for midi transmission

## Known issues

### The pedalboard have lag
This can happen when the pedalboard is connected to a computer, but no sofware
use the pedalboard. In this case, the arduino try to send midi data but the
computer does'nt retrieve them and the arduino stay blocked until a timeout
ends. This timeout is defined in the MIDIUSB library.
