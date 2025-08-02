#include "CPU.h"

#include <fstream>

#include <iostream>
using namespace std;

CPU::CPU()
{
    loadFont();
    pc = START_ADDR;
    I = 0;
    sp = 0;
    st = 0;
    dt = 0;

    for ( int i = 0; i < 16; i++ )
    {
        registers[i] = 0;
        stack[i] = 0;
        keys[i] = 0;
    }
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

    I = 0;

    srand( (unsigned) time(NULL) ); // Seed for RNG
}

bool CPU::loadRom(char const* f)
{
    ifstream file(f, ios::ate | ios::binary);

    if ( !file.is_open() )
    {
        cout << "Couldn't open file: " << f;
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

void CPU::cycle()
{
    // Fetch instruction from memory
    // Merges the next 2 bytes together to form the opcode
    opcode = memory[pc] << 8 | memory[pc+1];
    pc += 2;

    uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    uint8_t Vy = ( opcode & 0x00F0 ) >> 4;
    uint8_t kk = opcode & 0x00FF;

    // Decode the instruction and execute
    switch ( ( opcode & 0xF000 ) >> 12 )
    {
        case 0:
            switch ( opcode & 0x000F )
            {
                case 0:         // 00E0: CLS
                    CLS();
                    break;
                
                case 0x000E:    // 00EE: RET
                    RET();
                    break;
                
                default:
                    cout << "Error reading opcode: " << hex << opcode << endl;
                    break;
            }

            break;

        case 1: // 1nnn: JP addr
            JP_ADDR();
            break;
        
        case 2: // 2nnn: CALL addr
            CALL_ADDR();
            break;

        case 3: // 3xkk: SE Vx, byte
            SE_Vx_BYTE(Vx, kk);
            break;

        case 4: // 4xkk: SNE Vx, byte
            SNE_Vx_BYTE(Vx, kk);
            break;
        
        case 5: // 5xy0: SE Vx, Vy
            SE_Vx_Vy(Vx, Vy);
            
            break;
        
        case 6: // 6xkk: LD Vx, byte
            LD_Vx_BYTE(Vx, kk);            
            break;

        case 7: // 7xkk: ADD Vx, byte
            ADD_Vx_BYTE(Vx, kk);
            break;

        case 8:
            switch( opcode & 0x000F )
            {
                case 0: // 8xy0: LD Vx, Vy
                    LD_Vx_Vy(Vx, Vy);
                    break;
                
                case 1: // 8xy1: OR Vx, Vy
                    OR_Vx_Vy(Vx, Vy);
                    break;

                case 2: // 8xy2: AND Vx, Vy
                    AND_Vx_Vy(Vx, Vy);
                    break;

                case 3: // 8xy3: XOR Vx, Vy
                    XOR_Vx_Vy(Vx, Vy);
                    break;
                
                case 4: // 8xy4: ADD Vx, Vy
                    ADD_Vx_Vy(Vx, Vy);
                    break;
                
                case 5: // 8xy5: SUB Vx, Vy
                    SUB_Vx_Vy(Vx, Vy);
                    break;
                
                case 6: // 8xy6: SHR Vx
                    SHR_Vx(Vx);
                    break;
                
                case 7: // 8xy7: SUBN Vx, Vy
                    SUBN_Vx_Vy(Vx, Vy);
                    break;
                
                case 0x000E: // 8xyE: SHL Vx
                    SHL_Vx(Vx);
                    break;
                default:
                    cout << "Error reading opcode: " << hex << opcode << endl;
                    break;
            }

            break;

        case 9: // 9xy0: SNE Vx, Vy
            SNE_Vx_Vy(Vx, Vy);
            break;

        case 0x000A: // Annn: LD I, addr
            LD_I_ADDR();
            break;
        
        case 0x000B: // Bnnn JP V0, addr
            JP_V0_ADDR();
            break;
        
        case 0x000C: // Cxkk: RND Vx, byte
            RND_Vx_BYTE(Vx, kk);
            break;

        case 0x000D: // Dxyn: DRW Vx, Vy, nibble
            DRW_Vx_Vy_NIBBLE(Vx, Vy);
            break;

        case 0x000E:
            switch( opcode & 0x000F )
            {
                case 0x000E: // Ex9E: SKP Vx
                    SKP_Vx(Vx);
                    break;
                
                case 1: // ExA1: SKNP Vx
                    SKNP_Vx(Vx);
                    break;
                
                default:
                    cout << "Error reading opcode: " << hex << opcode << endl;
                    break;
            }
            break;

        case 0x000F:
            switch( opcode & 0x000F )
            {
                case 7: // Fx07: LD Vx, DT
                    LD_Vx_DT(Vx);
                    break;

                case 0x000A: // Fx0A: LD Vx, K
                    LD_Vx_K(Vx);
                    break;
                
                case 5:
                    // Switch table to handle Fx15, Fx55, and Fx65
                    switch( ( opcode & 0x00F0 ) >> 4 )
                    {
                        case 1: // Fx15: LD DT, Vx
                            LD_DT_Vx(Vx);
                            break;

                        case 5: // Fx55: LD [I], Vx
                            LD_I_Vx(Vx);
                            break;
                        
                        case 6: // Fx65: LD Vx, [I]
                            LD_Vx_I(Vx);
                            break;
                        
                        default:
                            cout << "Error reading opcode: " << hex << opcode << endl;
                            break;
                    }

                    break;
                    
                case 8: // Fx18: LD ST, Vx
                    LD_ST_Vx(Vx);
                    break;
                
                case 0x000E: // Fx1E: ADD I, Vx
                    ADD_I_Vx(Vx);
                    break;
                
                case 9: // Fx29: LD F, Vx
                    LD_F_Vx(Vx);
                    break;
                
                case 3: // Fx33: LD_B_Vx
                    LD_B_Vx(Vx);
                    break;
            }
            break;
        
        default:
            cout << "Error reading opcode: " << opcode << endl;
            break;
    }

    if ( dt > 0 )
    {
        dt--;
    }

    if ( st > 0 )
    {
        st--;
    }
}

void CPU::setKey(int k, int p)
{
    keys[k] = p;
 }

uint32_t* CPU::getDisplay()
{
    return display;
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
    sp--;           // Decrement stack pointer
    pc = stack[sp]; // Set program counter to address at top of stack
}

// Jump to location nnn
void CPU::JP_ADDR()
{
    pc = opcode & 0x0FFF; // Set program counter to nnn, which is extracted from opcode by applying a bitmask
}

// Call subroutine at nnn
void CPU::CALL_ADDR()
{
    stack[sp] = pc;         // Puts program counter at the top of stack
    sp++;
    pc = opcode & 0x0FFF;   // Set program counter to nnn, which is extracted from opcode by applying a bitmask
}

// Skip next instruction if Vx == kk
void CPU::SE_Vx_BYTE(uint8_t Vx, uint8_t byte)
{
    if ( registers[Vx] == byte )
    {
        pc += 2;
    }
}

// Skip next instruction if Vx != kk
void CPU::SNE_Vx_BYTE(uint8_t Vx, uint8_t byte)
{
    if ( registers[Vx] != byte )
    {
        pc += 2;
    }
}

// Skip next instruction if Vx = Vy
void CPU::SE_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    if ( registers[Vx] == registers[Vy] )
    {
        pc += 2;
    }
}

// Set Vx = kk
void CPU::LD_Vx_BYTE(uint8_t Vx, uint8_t byte)
{
    registers[Vx] = byte;
}

// Set Vx = Vx + kk
void CPU::ADD_Vx_BYTE(uint8_t Vx, uint8_t byte)
{
    registers[Vx] += byte;
}

// Set Vx = Vy
void CPU::LD_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    registers[Vx] = registers[Vy];
}

// Set Vx = Vx OR Vy
void CPU::OR_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    registers[Vx] |= registers[Vy];
}

// Set Vx = Vx AND Vy
void CPU::AND_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    registers[Vx] &= registers[Vy];
}

// Set Vx = Vx XOR Vy
void CPU::XOR_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    registers[Vx] ^= registers[Vy];
}

// Set Vx = Vx + Vy, set VF = carry
void CPU::ADD_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    uint16_t sum = registers[Vx] + registers[Vy];
    registers[Vx] = (uint8_t) sum & 0x00FF;
    if ( sum > 255 )
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

}

// Set Vx = Vx - Vy, set VF = NOT borrow
void CPU::SUB_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    uint8_t diff = (uint8_t) registers[Vx] - (uint8_t) registers[Vy];
    int carry = registers[Vx] >= registers[Vy];

    registers[Vx] = diff;
    registers[0xF] = carry;
}

// Set Vx = Vx SHR 1
void CPU::SHR_Vx(uint8_t Vx)
{
    registers[0xF] = registers[Vx] & 0x01;
    uint8_t val = registers[0xF];
    registers[Vx] = registers[Vx] / 2;
    registers[0xF] = val;
}

// Set Vx = Vy - Vx, set VF = NOT borrow
void CPU::SUBN_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    registers[Vx] = registers[Vy] - registers[Vx];
    registers[0xF] = registers[Vx] <= registers[Vy];
}

// Set Vx = Vx SHL 1
void CPU::SHL_Vx(uint8_t Vx)
{
    uint8_t f_val = ( registers[Vx] & 0x80 ) >> 7;
    registers[Vx] *= 2;
    registers[0xF] = f_val;
}

// Skip next instruction if Vx != Vy
void CPU::SNE_Vx_Vy(uint8_t Vx, uint8_t Vy)
{
    if ( registers[Vx] != registers[Vy] )
    {
        pc += 2;
    }
}

// Set I = nnn
void CPU::LD_I_ADDR()
{
    I = opcode & 0x0FFF;
}

// Jump to location nnn + V0
void CPU::JP_V0_ADDR()
{
    pc = ( opcode & 0x0FFF ) + registers[0];
}

// Set Vx = random byte AND kk.
void CPU::RND_Vx_BYTE(uint8_t Vx, uint8_t byte)
{
    int random = rand() % 256;
    registers[Vx] = random & byte;
}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
void CPU::DRW_Vx_Vy_NIBBLE(uint8_t Vx, uint8_t Vy)
{
    uint8_t x_coord = registers[Vx] % 64;
    uint8_t y_coord = registers[Vy] % 32;

    uint8_t n = opcode & 0x000F;
    for ( int i = 0; i < n; i++ ) // Reads n bytes
    {
        uint8_t byte = memory[I + i];

        for ( int j = 0; j < 8; j++ )
        {
            int d = x_coord + j + 64*( y_coord + i );
            uint32_t pixel = display[d]; // Gets address of correspnding pixel from display
            uint8_t bit = byte & ( 0x80 >> j );

            if ( bit )
            {
                pixel ^= 0xFFFFFFFF;
                if ( display[d] == 0xFFFFFFFFF )
                {
                    registers[0xF] = 1;
                }
                else
                {
                    registers[0xF] = 0;
                }

                display[d] = pixel;
            }
        }
    }
}

// Skip next instruction if key with the value of Vx is pressed
void CPU::SKP_Vx(uint8_t Vx)
{
    if ( keys[registers[Vx]] )
    {
        pc += 2;
    }
}

// Skip next instruction if key with the value of Vx is not pressed
void CPU::SKNP_Vx(uint8_t Vx)
{
    if ( !keys[registers[Vx]] )
    {
        pc += 2;
    }
}

// Fx07 - LD Vx, DT
void CPU::LD_Vx_DT(uint8_t Vx)
{
    registers[Vx] = dt;
}

// Wait for a key press, store the value of the key in Vx
void CPU::LD_Vx_K(uint8_t Vx)
{
    bool key_pressed = false;
    for ( int i = 0; i < 16; i++ )
    {
        if ( keys[i] == 1 )
        {
            key_pressed = true;
            registers[Vx] = i;
            break;
        }
    }

    if ( !key_pressed )
    {
        pc -= 2; // Causes this instruction to run again
    }
}

// Set delay timer = Vx
void CPU::LD_DT_Vx(uint8_t Vx)
{
    dt = registers[Vx];
}

// Set sound timer = Vx
void CPU::LD_ST_Vx(uint8_t Vx)
{
    st = registers[Vx];
}

// Set I = I + Vx
void CPU::ADD_I_Vx(uint8_t Vx)
{
    I += registers[Vx];
}

// Set I = location of sprite for digit Vx
void CPU::LD_F_Vx(uint8_t Vx)
{  
    // Register Vx will be holding location of font in memory
    // As each font character uses 5 bytes, it goes to the start of the fontset
    // And moves forward by the location of the character * 5
    I = FONT_ADDR + registers[Vx] * 5;  
}

// Store BCD representation of Vx in memory locations I, I+1, and I+2
void CPU::LD_B_Vx(uint8_t Vx)
{
    memory[I] = ( registers[Vx] / 100) % 10;
    memory[I+1] = ( registers[Vx] / 10 ) % 10;
    memory[I+2] = registers[Vx] % 10;
}

// Store registers V0 through Vx in memory starting at location I
void CPU::LD_I_Vx(uint8_t Vx)
{
    int it = I;
    for ( int r = 0; r <= Vx; r++ ) {
        memory[it] = registers[r];
        it++;
    }
}

// Read registers V0 through Vx from memory starting at location I
void CPU::LD_Vx_I(uint8_t Vx)
{
    // uint8_t Vx = ( opcode & 0x0F00 ) >> 8;
    int it = I;
    for ( int r = 0; r <= Vx; r++ ) {
        registers[r] = memory[it];
        it++;
    }
}
