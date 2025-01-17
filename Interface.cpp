#include "Interface.h"
#include <iostream>

using namespace std;

Interface::Interface()
{
    window = nullptr;
    renderer = nullptr;
    texture = nullptr;
}

Interface::~Interface()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Interface::initialize(char* title, int w_window, int h_window, int w_texture, int h_texture)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_window, h_window, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w_texture, h_texture);
}

void Interface::refreshDisplay(void* pixels)
{
    SDL_UpdateTexture(texture, nullptr, pixels, 256);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Interface::getInput(int& k, int& p)
{
    SDL_Event event;
    if ( SDL_PollEvent(&event) == 0 ) // Exit if no event occured
    {
        return false;
    }

    if ( event.type == SDL_QUIT )
    {
        return true;
    }
    
    if ( event.type == SDL_KEYDOWN )
    {
        p = 1;
    }
    else if ( event.type == SDL_KEYUP ){
        p = 0;
    }
    else { // If the event is not a keyboard event, return from function
        return false;
    }

    // Checks what key was pressed
    // Keybind layout is set to resemble the CHIP-8 hexadecimal keypad using the left side of the keyboard
    switch( event.key.keysym.scancode )
    {
        case SDL_SCANCODE_X: // X: 0
            k = 0;
            break;
        
        case SDL_SCANCODE_1: // 1: 1
            k = 1;
            break;
        
        case SDL_SCANCODE_2: // 2: 2
            k = 2;
            break;
        
        case SDL_SCANCODE_3: // 3: 3
            k = 3;
            break;
        
        case SDL_SCANCODE_Q: // Q: 4
            k = 4;
            break;
        
        case SDL_SCANCODE_W: // W: 5
            k = 5;
            break;
        
        case SDL_SCANCODE_E: // E: 6
            k = 6;
            break;
        
        case SDL_SCANCODE_A: // A: 7
            k = 7;
            break;
        
        case SDL_SCANCODE_S: // S: 8
            k = 8;
            break;
        
        case SDL_SCANCODE_D: // D: 9
            k = 9;
            break;
        
        case SDL_SCANCODE_Z: // Z: A
            k = 10;
            break;
        
        case SDL_SCANCODE_C: // C: B
            k = 11;
            break;
        
        case SDL_SCANCODE_4: // 4: C
            k = 12;
            break;
        
        case SDL_SCANCODE_R: // R: D
            k = 13;
            break;
        
        case SDL_SCANCODE_F: // F: E
            k = 14;
            break;
        
        default: // Default is V: F
            k = 15;
            break;
    }

    return false;
}