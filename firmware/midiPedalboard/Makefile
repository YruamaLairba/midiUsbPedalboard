#arduino 1.6.9 and micro does'nt seems to work with arduino-mk
#force version because autodetect of arduino-makefile is wrong
ARDUINO_VERSION = 10803
ARDUINO_DIR = /opt/arduino-1.8.3
ARDMK_DIR = ~/arduino/Arduino-Makefile
AVR_TOOLS_DIR = /opt/arduino-1.8.3/hardware/tools/avr
BOARD_TAG = micro
MONITOR_PORT = /dev/ttyACM0
ARDUINO_QUIET = 1
#USER_LIB_PATH := $(realpath ${HOME}/arduino/libraries)
ARDUINO_LIBS = MIDIUSB SPI Wire SSD1306Ascii EEPROM
OPTIMIZATION_LEVEL = s

CXXFLAGS= -Wall -Wextra -Wsign-conversion -pedantic -fdiagnostics-show-option
include ${ARDMK_DIR}/Arduino.mk

