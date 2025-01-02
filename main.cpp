#include "CPU.h"
#include "Interface.h"

int main(int argc, char* argv[])
{
    CPU* cpu = new CPU();
    bool success = cpu->loadRom(argv[1]);
    
    if ( !success )
    {
        return 0;
    }

    Interface* interface = new Interface();
    interface->initialize(argv[1], 64*10, 32*10, 64, 32);

    bool quit = false;
    while ( !quit ) // Emulation loop
    {
        // Run emulation
    }

    delete cpu;
    delete interface;
    return 0;
}