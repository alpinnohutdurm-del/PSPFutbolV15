TARGET = EBOOT
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSP Futbol V15

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
