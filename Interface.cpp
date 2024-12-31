#include "Interface.h"
#include <iostream>

using namespace std;

Interface::Interface(char* title, int w_window, int h_window, int w_texture, int h_texture)
{
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        cout << "SDL could not be initialized: " << SDL_GetError() << endl;
    }
    else
    {
        cout << "SDL successfully initialized" << endl;
    }

    window = SDL_CreateWindow(title, 0, 0, w_window, h_window, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w_texture, h_texture);
}

Interface::~Interface()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}