#include "CPU.h"

int main(int argc, char* argv[])
{
    CPU* cpu = new CPU();
    bool success = cpu->loadRom(argv[1]);
    
    if ( !success )
    {
        return 0;
    }

    delete cpu;
    return 0;
}