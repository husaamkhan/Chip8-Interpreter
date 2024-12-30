#include "Chip8.h"

int main(int argc, char* argv[])
{
    Chip8* chip8 = new Chip8();
    bool success = chip8->loadRom(argv[1]);
    
    if ( !success )
    {
        return 0;
    }

    return 0;
}