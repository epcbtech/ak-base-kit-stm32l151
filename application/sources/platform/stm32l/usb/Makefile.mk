include sources/platform/stm32l/Libraries/STM32_USB-FS-Device_Driver/Makefile.mk

CFLAGS += -I./sources/platform/stm32l/usb/inc
CPPFLAGS += -I./sources/platform/stm32l/usb/inc

VPATH += sources/platform/stm32l/usb/src

# C source files
SOURCES += sources/platform/stm32l/usb/src/hw_config.c
SOURCES += sources/platform/stm32l/usb/src/usb_desc.c
SOURCES += sources/platform/stm32l/usb/src/usb_endp.c
SOURCES += sources/platform/stm32l/usb/src/usb_istr.c
SOURCES += sources/platform/stm32l/usb/src/usb_prop.c
SOURCES += sources/platform/stm32l/usb/src/usb_pwr.c
