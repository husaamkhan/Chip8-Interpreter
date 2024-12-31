#ifndef CPU_H
#define CPU_H

#include <cstdint>

using namespace std;

class CPU
{
    public:
        CPU();
        ~CPU();
        
        bool loadRom(char const* f);

        // Standard Chip-8 instructions
        void SYS_ADDR();
        void CLS();
        void RET();
        void JP_ADDR();
        void CALL_ADDR();
        void SE_Vx_BYTE();
        void SNE_Vx_BYTE();
        void SE_Vx_Vy();
        void LD_Vx_BYTE();
        void ADD_Vx_BYTE();
        void LD_Vx_Vy();
        void OR_Vx_Vy();
        void AND_Vx_Vy();
        void XOR_Vx_Vy();
        void ADD_Vx_Vy();
        void SUB_Vx_Vy();
        void SHR_Vx_Vy();
        void SUBN_Vx_Vy();
        void SHL_Vx_Vy();
        void SNE_Vx_Vy();
        void LD_I_ADDR();
        void JP_V0_ADDR();
        void RND_Vx_BYTE();
        void DRW_Vx_Vy_NIBBLE();
        void SKP_Vx();
        void SKNP_Vx();
        void LD_Vx_DT();
        void LD_Vx_K();
        void LD_DT_Vx();
        void LD_ST_Vx();
        void ADD_I_Vx();
        void LD_F_Vx();
        void LD_B_Vx();
        void LD_I_Vx();
        void LD_Vx_I();

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

#endif // CPU_H