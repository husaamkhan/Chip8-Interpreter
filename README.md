# Chip 8 Interpreter
This repository contains the source code for a CHIP-8 interpreter that can be used to run any CHIP-8 program

## Compilation
### Windows:
1. mkdir build
2. cd build
3. cmake ..
4. cmake --build . --config Release

Executable is stored in /build/Release

## Usage
The interpreter can run CHIP-8 ROMs downloaded off of the internet. You can run the ROM with the following command:
### Windows:
`./chip8.exe <Speed> <Path to ROM>`
