#pragma once
#include <SDL2/SDL.h>

struct SDLData {
    SDL_Window* window;
    SDL_Surface* surface;
};

SDLData PrepareSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT);