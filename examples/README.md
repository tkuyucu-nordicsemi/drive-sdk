Anki Drive SDK Examples
=======================

These examples show how to use the Anki Drive SDK to detect, display, connect to and control vehicles. 

[BlueZ]: http://www.bluez.org

### vehicle-scan

A linux command line utility to scan for Anki Drive vehicles using Bluetooth LE and display information advertised by vehicles.
This utility shows how to use the data parsing methods to extract vehicle information from Bluetooth LE advertising data packets.
`vehicle-scan` requires [Bluez][] and is licensed under the GNU Public License v3.

#### vehicle-tool

An interactive command line shell for connecting and controlling Anki Drive vehicles.
This program demonstrates the Bluetooth LE connection procedure and shows how to interact use the message protocol to interact with vehicles.
`vehicle-tool` requires [Bluez][] and is licensed under the GNU Public License v3.
