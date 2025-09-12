# Chip 8 Interpreter
This repository contains a CHIP-8 interpreter written in C++ with an SDL2-based interface for graphics, input, and sound. It can be used to run any standard CHIP-8 ROM.

## Features
- Emulates the full CHIP-8 instruction set
- SDL2-based graphics and input handling
- Simple audio beep support
- Adjustable emulation speed

## Dependencies
[SDL2](https://www.libsdl.org/), a cross-platform library providing access to audio, and input devices, and graphics through OpenGL and Direct3D.\n
SDL2 must be installed on your system before compiling.

## Compilation
### Linux and Windows:
`mkdir build`
`cd build`
`cmake ..`
`cmake --build . --config Release`

Executable is stored in:
- **Linux**: build/chip8
- **Windows**: build/Release/chip8.exe

## Usage
You can run any CHIP-8 ROM by passing the desired emulation speed and the path to the ROM file as arguments.
### Windows:
`./chip8.exe <Speed> <Path-to-ROM>`
### Linux:
`./chip8 <Speed> <Path-to-ROM>`

- **<Speed>**: Controls the emulation cycle frequency
- **<Path-to-ROM>**: Path to your CHIP-8 program file (e.g., roms/PONG.ch8).
- **Example**: ./chip8 200 roms/PONG.ch8

### Key mapping
The original CHIP-8 used a 16-key hexadecimal keypad arranged like this:
|     |     |     |     |
|-----|-----|-----|-----|
| **1** | **2** | **3** | **C** |
| **4** | **5** | **6** | **D** |
| **7** | **8** | **9** | **E** |
| **A** | **0** | **B** | **F** |

This interpreter maps them to your keyboard like this:
|     |     |     |     |
|-----|-----|-----|-----|
| **1** | **2** | **3** | **4** |
| **Q** | **W** | **E** | **R** |
| **A** | **S** | **D** | **F** |
| **Z** | **X** | **C** | **V** |

## Possible Future Improvements
- Compatibility for Super CHIP-8 programs
- Configurable key mapping
