#include "CPU.h"
#include "Interface.h"
#include <ctime>

#include <iostream>
using namespace std;

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

    bool running = true;

    time_t current_time;
    time_t last_time;
    time(&last_time);
    int k = -1;
    int p = -1;

    while ( running ) // Emulation loop
    {
        // Get user input, and update running flag based on whether or not user chooses to quit
        running = !interface->getInput(k, p);

        // If a key was pressed or release, set that key to pressed/released in cpu
        if ( !( k == -1 || p == -1 ) ) 
        {
            cpu->setKey(k, p);
        }

        // Emulator runs at 60hz, so it waits until a second passes before running one cpu cycle
        time(&current_time);
        if ( difftime(current_time, last_time) >= 1 )
        {
            break;
        }
    }

    delete cpu;
    delete interface;
    return 0;
}