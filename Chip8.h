#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>

using namespace std;

class Chip8
{
    public:
        Chip8();
        ~Chip8();
        
        bool loadRom(char const* f);

    private:
        uint8_t registers[16];      // 16 8-bit general purpose registers
        uint8_t memory[4096];          // 4KB of RAM
        uint8_t dt;                 // Special purpose 8-bit register for delay timer
        uint8_t st;                 // Special purpose 8-bit register for sound timer
        uint16_t pc;                // 16-bit program counter
        uint8_t sp;                 // 8-bit stack pointer
        uint16_t stack[16];         // 16 16-bit values in stack
        uint8_t keypad[16];         // 16-key hexadecimal keypad
        uint32_t display[64*32];    // 64x32 pixel display
        uint16_t opcode;            // 16-bit opcode

        const unsigned int START_ADDR = 0x200; // Start of most Chip-8 programs
};

#endif // CHIP8_H