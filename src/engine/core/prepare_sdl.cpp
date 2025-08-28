#include <SDL2/SDL.h>
#include <iostream>
#include <prepare_sdl.h>
#include "debug.h"

using namespace std;

SDLData PrepareSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL error: " << SDL_GetError() << endl;
        return {nullptr, nullptr};
    }

    AddLog("SDL initialized successfully");

    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC
    );
    if (!window) {
        cerr << "SDL error: " << SDL_GetError() << endl;
        SDL_Quit();
        return {nullptr, nullptr};
    }
    AddLog("Window created successfully.");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "SDL error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return {nullptr, nullptr};
    }
    AddLog("Renderer created successfully.");

    AddLog("PrepareSDL Done.");

    return {window, renderer};
}
