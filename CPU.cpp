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

// Clears display
void CPU::CLS()
{
    for ( int i = 0; i < (64*32); i++ ) // Sets entire video buffer to 0
    {
        display[i] = 0;
    }
}

// Return from subroutine
void CPU::RET()
{
    pc = stack[sp]; // Set program counter to address at top of stack
    sp--;           // Decrement stack pointer
}

// Jump to location nnn
void CPU::JP_ADDR()
{
    pc = opcode & 0x0FFF; // Set program counter to nnn, which is extracted from opcode by applying a bitmask
}

// Call subroutine at nnn
void CPU::CALL_ADDR()
{
    sp++;
    stack[sp] = pc;         // Puts program counter at the top of stack
    pc = opcode & 0x0FFF;   // Set program counter to nnn, which is extracted from opcode by applying a bitmask
}

// Skip next instruction if Vx == kk
void CPU::SE_Vx_BYTE()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;   // Get register Vx by applying bitmask and shifting
    uint8_t kk = opcode & 0x00FF;

    if ( registers[Vx] == kk )
    {
        pc += 2;
    }
}

// Skip next instruction if Vx != kk
void CPU::SNE_Vx_BYTE()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t kk = opcode & 0x00FF;

    if ( registers[Vx] != kk )
    {
        pc += 2;
    }
}

// Skip next instruction if Vx = Vy
void CPU::SE_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    if ( registers[Vx] == registers[Vy] )
    {
        pc += 2;
    }
}

// Set Vx = kk
void CPU::LD_Vx_BYTE()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t kk = opcode & 0x00FF;

    registers[Vx] = kk;
}

// Set Vx = Vx + kk
void CPU::ADD_Vx_BYTE()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t kk = opcode & 0x00FF;

    registers[Vx] += kk;
}

// Set Vx = Vy
void CPU::LD_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    registers[Vx] = registers[Vy];
}

// Set Vx = Vx OR Vy
void CPU::OR_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    registers[Vx] = registers[Vx] || registers[Vy];
}

// Set Vx = Vx AND Vy
void CPU::AND_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    registers[Vx] = registers[Vx] && registers[Vy];
}

// Set Vx = Vx XOR Vy
void CPU::XOR_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    registers[Vx] = registers[Vx] ^ registers[Vy];
}

// Set Vx = Vx + Vy, set VF = carry
void CPU::ADD_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    if ( registers[Vx] + registers[Vy] > 255 )
    {
        registers[Vy] = 1;
    }
    else
    {
        registers[Vy] = 0;
    }

    registers[Vx] = ( registers[Vx] + registers[Vy] ) && 0xFF00;
}

// Set Vx = Vx - Vy, set VF = NOT borrow
void CPU::SUB_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    if ( registers[Vx] > registers[Vy] )
    {
        registers[0xF000] = 1;
    }
    else
    {
        registers[0xF000] = 0;
    }

    registers[Vx] -= registers[Vy];
}

// Set Vx = Vx SHR 1
void CPU::SHR_Vx()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;

    if ( ( registers[Vx] && 0x0001 ) == 1 )
    {
        registers[0xF000] = 1;
    }
    else
    {
        registers[0xF000] = 0;
    }

    registers[Vx] = registers[Vx] / 2;
}

// Set Vx = Vy - Vx, set VF = NOT borrow
void CPU::SUBN_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    if ( registers[Vx] < registers[Vy] )
    {
        registers[0xF000] = 1;
    }
    else
    {
        registers[0xF000] = 0;
    }

    registers[Vx] = registers[Vy] - registers[Vx];
}

// Set Vx = Vx SHL 1
void CPU::SHL_Vx()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;

    if ( ( registers[Vx] && 0x8000 ) == 1 )
    {
        registers[0xF000] = 1;
    }
    else
    {
        registers[0xF000] = 0;
    }

    registers[Vx] *= 2;
}

// Skip next instruction if Vx != Vy
void CPU::SNE_Vx_Vy()
{
    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;

    if ( registers[Vx] != registers[Vy] )
    {
        pc += 2;
    }
}

void CPU::LD_I_ADDR()
{}

void CPU::JP_V0_ADDR()
{}

void CPU::RND_Vx_BYTE()
{}

void CPU::DRW_Vx_Vy_NIBBLE()
{}

void CPU::SKP_Vx()
{}

void CPU::SKNP_Vx()
{}

void CPU::LD_Vx_DT()
{}

void CPU::LD_Vx_K()
{}

void CPU::LD_DT_Vx()
{}

void CPU::LD_ST_Vx()
{}

void CPU::ADD_I_Vx()
{}

void CPU::LD_F_Vx()
{}

void CPU::LD_B_Vx()
{}

void CPU::LD_I_Vx()
{}

void CPU::LD_Vx_I()
{}
