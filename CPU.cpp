#include "CPU.h"

#include <fstream>
#include <iostream>
#include <vector>

CPU::CPU()
{
    loadFont();
    pc = START_ADDR;
}

CPU::~CPU()
{}

void CPU::loadFont()
{
    uint8_t bytes[FONT_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for ( int i = 0; i < FONT_SIZE; i++ )
    {
        memory[FONT_ADDR+i] = bytes[i];
    }
}

bool CPU::loadRom(char const* f)
{
    ifstream file(f, ios::ate | ios::binary);

    if ( file.bad() )
    {
        cout << "Couldn't read file: " << f;
        return false;
    }

    // Create buffer for file contents
    streampos size = file.tellg();
    char* buf = new char[size];

    file.seekg(0, ios::beg);    // Return to start of file
    file.read(buf, size);       // Read data from file into buffer
    file.close();

    for ( long i = 0; i < size; i++ )
    {
        memory[START_ADDR + i] = buf[i]; // Load data from buffer into chip memory
    }

    delete[] buf;
    cout << "Successfully loaded file: '" << f << "' of size " << size << endl;
    return true;
}

void SYS_ADDR()
{}

void CLS()
{}

void RET()
{}

void JP_ADDR()
{}

void CALL_ADDR()
{}

void SE_Vx_BYTE()
{}

void SNE_Vx_BYTE()
{}

void SE_Vx_Vy()
{}

void LD_Vx_BYTE()
{}

void ADD_Vx_BYTE()
{}

void LD_Vx_Vy()
{}

void OR_Vx_Vy()
{}

void AND_Vx_Vy()
{}

void XOR_Vx_Vy()
{}

void ADD_Vx_Vy()
{}

void SUB_Vx_Vy()
{}

void SHR_Vx_Vy()
{}

void SUBN_Vx_Vy()
{}

void SHL_Vx_Vy()
{}

void SNE_Vx_Vy()
{}

void LD_I_ADDR()
{}

void JP_V0_ADDR()
{}

void RND_Vx_BYTE()
{}

void DRW_Vx_Vy_NIBBLE()
{}

void SKP_Vx()
{}

void SKNP_Vx()
{}

void LD_Vx_DT()
{}

void LD_Vx_K()
{}

void LD_DT_Vx()
{}

void LD_ST_Vx()
{}

void ADD_I_Vx()
{}

void LD_F_Vx()
{}

void LD_B_Vx()
{}

void LD_I_Vx()
{}

void LD_Vx_I()
{}
