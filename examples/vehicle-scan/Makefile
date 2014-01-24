CC=gcc

ANKI_SDK_ROOT=../..

BLUEZ_INCLUDE = -I$(BLUEZ_ROOT)/lib
ANKI_INCLUDE = -I$(ANKI_SDK_ROOT)/include

INCLUDES = $(BLUEZ_INCLUDE) $(ANKI_INCLUDE)
LIBS = -L$(ANKI_SDK_ROOT)/build/src -L$(BLUEZ_ROOT)/lib/.libs -lbluetooth-internal -lankidrive

CFLAGS = $(INCLUDES) $(LIBS)

DEPS = vehicle-scan.h
OBJ = vehicle-scan.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vehicle-scan: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core vehicle-scan 
