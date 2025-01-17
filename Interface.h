/*
    --Interface class--
    Purpose: Graphics rendering and keyboard input
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h> // Low-level Interface library

class Interface
{
    public:
        Interface();
        ~Interface();

        void initialize(char* title, int w_window, int h_window, int w_texture, int h_texture);
        void refreshDisplay(void* pixels);
        bool getInput(int& key, int& pressed);

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
};

#endif // INTERFACE_H