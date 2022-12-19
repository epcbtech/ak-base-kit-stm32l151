CFLAGS   += -I./sources/driver/led
CFLAGS   += -I./sources/driver/flash
CFLAGS   += -I./sources/driver/eepprom

CPPFLAGS += -I./sources/driver/led
CPPFLAGS += -I./sources/driver/flash
CPPFLAGS += -I./sources/driver/eepprom

VPATH += sources/driver/led
VPATH += sources/driver/eeprom
VPATH += sources/driver/flash

SOURCES += sources/driver/led/led.c
SOURCES += sources/driver/flash/flash.c
SOURCES_CPP += sources/driver/eeprom/eeprom.cpp
