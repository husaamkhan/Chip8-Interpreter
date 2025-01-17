#include "CPU.h"
#include "Interface.h"
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <string>

#include <iostream>
using namespace std;
using namespace chrono;

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

    int delay = stoi(argv[1]);

    bool running = true;

    auto last_time = high_resolution_clock::now();

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
            k = -1;
            p  = -1;
        }

        // Runs cycle based on the inputted frequency
        auto current_time = high_resolution_clock::now();
        float delta = std::chrono::duration<float, std::chrono::milliseconds::period>(current_time - last_time).count();
        if ( delta >= stoi(argv[1]) )
        {            
            cpu->cycle();
            last_time = high_resolution_clock::now();
            interface->refreshDisplay(cpu->getDisplay());
        }
    }

    delete cpu;
    delete interface;
    return 0;
}