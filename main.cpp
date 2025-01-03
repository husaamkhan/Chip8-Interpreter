#include "CPU.h"
#include "Interface.h"
#include <ctime>
#include <stdlib.h>

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    CPU* cpu = new CPU();
    bool success = cpu->loadRom(argv[2]);
    
    if ( !success )
    {
        return 0;
    }

    Interface* interface = new Interface();
    interface->initialize(argv[2], 64*10, 32*10, 64, 32);

    double delay = 1 / stoi(argv[1]);

    bool running = true;

    time_t current_time;
    time_t last_time;
    time(&last_time);
    int k = -1;
    int p = -1;

    string input;

    while ( running ) // Emulation loop
    {
        // Get user input, and update running flag based on whether or not user chooses to quit
        running = !interface->getInput(k, p);

        // If a key was pressed or release, set that key to pressed/released in cpu
        if ( !( k == -1 || p == -1 ) ) 
        {
            cpu->setKey(k, p);
        }

        // Emulator runs at 30hz, so it waits until 0.033 seconds passes before performing a cpu cycle
        time(&current_time);
        if ( running && difftime(current_time, last_time) >= 0.033 )
        {
            cpu->cycle();
            interface->refreshDisplay(cpu->getDisplay());
        }

        // cout << "Continue? (Y/N): ";
        // cin >> input;
        // cout << endl;

        // if ( input.compare("N") == 0 )
        // {
        //     running = false;
        // }
    }

    delete cpu;
    delete interface;
    return 0;
}