#pragma once
#include <SDL2/SDL.h>

struct SDLData {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

SDLData PrepareSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT);