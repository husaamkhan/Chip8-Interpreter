/*
    --Interface class--
    Purpose: Graphics rendering and keyboard input
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h> // Low-level Interface library

class Interface
{
    public:
        Interface(char* title, int w_window, int h_window, int w_texture, int h_texture);
        ~Interface();

        void refreshDisplay(char* pixels);

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
};

#endif // INTERFACE_H