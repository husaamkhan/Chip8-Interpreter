/*
    --CPU class--
    Purpose: All Chip-8 processing functionality
*/


#ifndef CPU_H
#define CPU_H

#include <cstdint>

using namespace std;

class CPU
{
    public:
        CPU();
        ~CPU();
        
        void loadFont();
        bool loadRom(char const* f);
        void cycle();
        void setKey(int k, int p);
        uint32_t* getDisplay();

        // Standard Chip-8 instructions
        void CLS();
        void RET();
        void JP_ADDR();
        void CALL_ADDR();
        void SE_Vx_BYTE(uint8_t Vx, uint8_t byte);
        void SNE_Vx_BYTE(uint8_t Vx, uint8_t byte);
        void SE_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void LD_Vx_BYTE(uint8_t Vx, uint8_t byte);
        void ADD_Vx_BYTE(uint8_t Vx, uint8_t byte);
        void LD_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void OR_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void AND_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void XOR_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void ADD_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void SUB_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void SHR_Vx(uint8_t Vx);
        void SUBN_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void SHL_Vx(uint8_t Vx);
        void SNE_Vx_Vy(uint8_t Vx, uint8_t Vy);
        void LD_I_ADDR();
        void JP_V0_ADDR();
        void RND_Vx_BYTE(uint8_t Vx, uint8_t byte);
        void DRW_Vx_Vy_NIBBLE(uint8_t Vx, uint8_t Vy);
        void SKP_Vx(uint8_t Vx);
        void SKNP_Vx(uint8_t Vx);
        void LD_Vx_DT(uint8_t Vx);
        void LD_Vx_K(uint8_t Vx);
        void LD_DT_Vx(uint8_t Vx);
        void LD_ST_Vx(uint8_t Vx);
        void ADD_I_Vx(uint8_t Vx);
        void LD_F_Vx(uint8_t Vx);
        void LD_B_Vx(uint8_t Vx);
        void LD_I_Vx(uint8_t Vx);
        void LD_Vx_I(uint8_t Vx);

    private:
        uint8_t registers[16];      // 16 8-bit general purpose registers
        uint16_t I;                // 16-bit register called I
        uint8_t memory[4096];       // 4KB of RAM
        uint8_t dt;                 // Special purpose 8-bit register for delay timer
        uint8_t st;                 // Special purpose 8-bit register for sound timer
        uint16_t pc;                // 16-bit program counter
        uint8_t sp;                 // 8-bit stack pointer
        uint16_t stack[16];         // 16 16-bit values in stack
        uint8_t keys[16];         // 16-key hexadecimal keypad
        uint32_t display[64*32];    // 64x32 pixel display
        uint16_t opcode;            // 16-bit opcode

        const unsigned int START_ADDR = 0x200;  // Start of most Chip-8 programs
        const unsigned int FONT_ADDR = 0x00;    // Start of font set
        const unsigned int FONT_SIZE = 80;      // 16 total characters, each represented with 5 bytes
};

#endif // CPU_H