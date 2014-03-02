# libbzle

This is a minimal library consisting of code from [BlueZ 5.15][bluez] that is required for Bluetooth LE.
The Anki Drive SDK only requires the C interface to access Bluetooth LE methods supported by the Linux kernel.
This small package simplifies the build procedure, but eliminating the requirement to install dependencies and build the entire BlueZ 5.x package.

[bluez]: http://www.bluez.org/

## Build

```
mkdir build
cd build
cmake ..
make
```

## Products

- `libbzle.a`: Static library.
- `include/bzle`: Public header files for Bluetooth LE and GATT functions.
- `hciconfig`: The `hciconfig` tool distributed with the BlueZ package.
This tool allows users to configure Bluetooth USB dongles.


