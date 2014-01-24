CC=gcc

ROOT=/home/pi/rpi
ANKI_SDK_ROOT=$(ROOT)/DriveSDK
BLUEZ_ROOT=$(ROOT)/bluez

BLUEZ_INCLUDE = -I$(BLUEZ_ROOT)/lib
ANKI_INCLUDE = -I$(ANKI_SDK_ROOT)/include

INCLUDES = -I. $(BLUEZ_INCLUDE) $(ANKI_INCLUDE)
LIBS = -L. -L/usr/lib/arm-linux-gnueabihf -Wl,-rpath=/usr/lib/arm-linux-gnueabihf -L$(ANKI_SDK_ROOT)/build/src -lbluetooth -lankidrive -lreadline -lc 

DBUS_CFLAGS = `pkg-config --cflags --libs dbus-1`
GLIB_CFLAGS = `pkg-config --cflags --libs glib-2.0`
CFLAGS = $(INCLUDES) $(LIBS) $(GLIB_CFLAGS) $(DBUS_CFLAGS)

DEPS = att-database.h att.h gatt.h gattrib.h vehicle_tool.h 
OBJ = att.o gatt.o gattrib.o vehicle_tool.o vehicle_cmd.o utils.o log.o btio/btio.o client/display.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vehicle-tool: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o btio/*.o client/*.o lib/*.o *~ core vehicle-tool 
