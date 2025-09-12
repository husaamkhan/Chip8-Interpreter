# Chip 8 Interpreter
This repository contains the source code for a CHIP-8 interpreter that can be used to run any CHIP-8 program

## Dependencies
For its interface, this program uses SDL2, a cross-platform library for low level access to audio, input peripheral devices, and graphics hardware using OpenGL and Direct3D. 
https://www.libsdl.org/

## Compilation
### Windows:
1. mkdir build
2. cd build
3. cmake ..
4. cmake --build . --config Release

Executable is stored in /build/Release

## Usage
The interpreter can run CHIP-8 ROMs downloaded off of the internet. You can run the ROM from a terminal with the following command:
### Windows:
`./chip8.exe <Speed> <Path to ROM>`
