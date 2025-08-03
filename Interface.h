/*
    --Interface class--
    Purpose: Graphics rendering and keyboard input
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h> // Low-level Interface library

#define SAMPLE_RATE 44100
#define CHANNELS 1
#define SAMPLES 1024
#define AMPLITUDE 20000
#define FREQUENCY 440

class Interface
{
    public:
        Interface();
        ~Interface();

        bool initialize(char* title, int w_window, int h_window, int w_texture, int h_texture);
        void playAudio();
        void stopAudio();
        void refreshDisplay(void* pixels);
        bool getInput(int& key, int& pressed);

    private:
        static void generateAudioSamples(void* userdata, Uint8* stream, int len);
        bool initialized;

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_AudioSpec audio_spec;
        Sint16 audio_buffer[SAMPLES];
        double audio_phase;
        int remaining_samples;
};

#endif // INTERFACE_H