Anki Drive SDK
==============

The Anki Drive SDK is a C implementation of the message protocols and data parsing routines necessary for communicating with Anki Drive vehicles. 

The Anki Drive SDK is licensed under the Apache 2.0 license. Projects in the `examples` folder are released under separate licenses.

- website: http://developer.anki.com/DriveSDK
- StackOverflow Tag: anki-drive-sdk
- Issues: [GitHub Issues](https://github.com/anki/DriveSDK/issues)
- Programming Guide: http://developer.anki.com/DriveSDK/programming-guide
- Mailing list: [Anki-Dev Google Group](https://groups.google.com/a/anki.com/forum/#!forum/anki-dev)

[bluez]: http://www.bluez.org/

Features
========

The initial release of the SDK has the minimal number of functions required to use the message protocol and parse information sent by vehicles.

* Parse vehicle info from Bluetooth LE `LOCAL_NAME` and `MANUFACTURER_DATA` advertisement data.
* Create messages to send commands to vehicles.
* Parse vehicle response messages.

The initial version provides a limited subset of the message protocol.
We hope to expand available messages and functionality in the future, once we can do so in a safe and stable way.

Optional dependencies
=====================

* [BlueZ][bluez] for example linux utilities. See `examples` folder.

Building the SDK
================

The Anki Drive SDK builds cleanly on Mac OS X and most linux distributions.
The SDK builds the `libankidrive` library, with public headers available in `include`.

The SDK is built using `CMake 2.8` (<http://www.cmake.org>) on all platforms.

     $ mkdir -p build && cd build

     # build library
     $ cmake ..
     $ make

     # build library + examples
     # set path to compiled bluez source
     $ export BLUEZ_ROOT=/path/to/bluez
     $ cmake .. -DBUILD_EXAMPLES=ON
     $ make



### Run Unit Tests

     $ cd build
     $ ./test/Test


