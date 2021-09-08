# Enercastlib
Enercastlib is a library to communicate with charge controllers:
- EPEVER MPPT Tracer1210AN
- Morningstar TS-45

The library offers access to the controllers' data and settings. 
It relies on a 3rd party library https://github.com/stephane/libmodbus for the communication over Modbus RTU protool.

The library is written in C++ and designed to run on Linux.

## Getting started 
### Prerequisites
Downolad and installation of libmodbus at  https://github.com/stephane/libmodbus is required.
### Installation

## Documentation
The documentation is available at

## Testing
Some tests are provided in tests directory. 
For a quick test of libmodbus, you can run the following programs:
```
./testEpever
./testMorningstar
```
Remember to change the path to your devices.

