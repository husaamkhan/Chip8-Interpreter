#include "Chip8.h"

#include <fstream>
#include <iostream>
#include <vector>

Chip8::Chip8()
{
    pc = START_ADDR;
}

Chip8::~Chip8() {}

bool Chip8::loadRom(char const* f)
{
    ifstream file(f, ios::ate | ios::binary);

    if ( file.bad() )
    {
        cout << "Couldn't read file: " << f;
        return false;
    }

    // Create buffer for file contents
    streampos size = file.tellg();
    auto buf = new char[size];

    file.seekg(0, ios::beg);    // Return to start of file
    file.read(buf, size);       // Read data from file into buffer
    file.close();

    for ( long i = 0; i < size; i++ )
    {
        memory[START_ADDR + i] = buf[i]; // Load data from buffer into chip memory
    }

    cout << "Successfully loaded file: '" << f << "' of size " << size << endl;
    return true;
}