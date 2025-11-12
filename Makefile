TARGET = HelloWorld
OBJS = main.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Hello World
PSP_EBOOT_ICON = NULL
PSP_EBOOT_PIC1 = NULL

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
