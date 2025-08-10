#include <SDL2/SDL.h>
#include <iostream>
#include "prepare_sdl.h"

using namespace std;

int PrepareSDL() {

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_INIT_VIDEO < 0) {
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
        return 1;
    } else {
        window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    }

}