#include <SDL2/SDL.h>
#include <iostream>
#include "prepare_sdl.h"

using namespace std;

int PrepareSDL() {

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;

    if (SDL_INIT_VIDEO < 0) {
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
        return 1;
    } else {
        window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

        if(window == nullptr) {
            std::cout << "SDL error: " << SDL_GetError() << std::endl;
            return 1;
        } else {
            cout << "SDL Window created successfully." << std::endl;
            surface = SDL_GetWindowSurface(window);
            if(surface == nullptr) {
                std::cout << "SDL error: " << SDL_GetError() << std::endl;
                return 1;
            } else {
                cout << "SDL Surface obtained successfully." << std::endl;
                return 0;
            }
        }
    }
}