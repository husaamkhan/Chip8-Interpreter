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
    if (argc < 3)
    {
        std::cerr << "Usage: ./chip8.exe <delay> <rom_file>" << endl;
    }

    auto cpu = std::make_unique<CPU>();
    if ( !cpu->loadRom(argv[2]))
    {
        return 0;
    }

    auto interface = std::make_unique<Interface>();
    interface->initialize(argv[2], 64*10, 32*10, 64, 32);

    // Takes cpu cycle speed in Hz and converts to cycle length in milliseconds
    int input = stoi(argv[1]);
    float cycle_length = 1000 / input;

    bool running = true;

    using clock = std::chrono::high_resolution_clock;
    auto last_time = clock::now();

    float acc = 0.0f;

    int k = -1;
    int p = -1;

    while (running)
    {
        auto current_time = clock::now();
        float delta = std::chrono::duration<float, std::chrono::milliseconds::period>(current_time - last_time).count();
        if (delta > 100.0f)
        {
            delta = 100.0f;
        }

        last_time = current_time;
        acc += delta;

        running = !interface->getInput(k, p);

        if ( !( k == -1 || p == -1 ) )
        {
            cpu->setKey(k, p);
            k = -1;
            p = -1;
        }

        while (acc >= cycle_length)
        {
            cpu->cycle();
            acc -= cycle_length;
        }

        interface->refreshDisplay(cpu->getDisplay());
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}