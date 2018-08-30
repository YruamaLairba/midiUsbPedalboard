# midiPedalboard

This is the firmware for a configurable midi USB foot controller with 4 footswitches and 1 expression pedal. The project is built around the Arduino micro board.

## License

I release this code under GPL V3 licence, the full text is in LICENSE.txt

## Building the firmware

1. Change the bootloader

   When you connect the USB port, the original bootloader writes 2 bytes in an unsafe way in the middle of the memory, and may corrupt some data. One solution is to use [Hoodloader 2](https://github.com/NicoHood/HoodLoader2).

2. Get additional libraries

   The following libraries can be installed from the library manager:
  
   * MIDIUSB
   * Adafruit GFX
   * Adafruit SSD1306

3. Open and build midiPedalboard.ino and load it into the board.

## Parts and pin layout

### Parts for the configuration interface
* a 128x64 SSD1306 screen, SPI version,
* a rotary encoder and 2 capacitors for debouncing. Connect the capacitors between ground and each output of the rotary encoder. Mine are 100&nbsp;nF but the value is not really important.
* 2 momentary push buttons, one for "ok", the other for "cancel"

### Foot control part
* 4 momentary (normally open) switches. I recommend footswitches with soft touch.
* 4 LEDs. They are used to show footswitch status.
* 4 resistors, put each of them in series with an LED to limits their current
* An expression pedal ;). You may also need a female jack connector. A switched connector is better because it can avoid a "floating input" when no expression pedal is connected.

### Pin layout
Most of the pins are in setup.h and can be changed. Exception are:

* MOSI of the Arduino, connected to the data input of the SSD1306 screen
* SCK of the Arduino, connected to the clock input of the SSD1306 screen
* pin 0/Rx of the Arduino, not yet used but reserved for midi reception
* pin 1/Tx of the Arduino, used for midi transmission

