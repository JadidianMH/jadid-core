#pragma once
#include <SDL2/SDL.h>
#include <string>

struct SDLData {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

SDLData PrepareSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE);