#include "Interface.h"
#include <iostream>
using namespace std;

Interface::Interface()
{
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        cout << "SDL could not be initialized: " << SDL_GetError() << endl;
    }
    else
    {
        cout << "SDL successfully initialized" << endl;
    }
}

Interface::~Interface()
{}