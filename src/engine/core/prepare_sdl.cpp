#include <SDL2/SDL.h>
#include <iostream>
#include <prepare_sdl.h>

using namespace std;

SDLData PrepareSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL error: " << SDL_GetError() << endl;
        return {nullptr, nullptr};
    }
    cout << "SDL initialized successfully." << endl;

    window = SDL_CreateWindow(
        "Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        cerr << "SDL error: " << SDL_GetError() << endl;
        SDL_Quit();
        return {nullptr, nullptr};
    }
    cout << "Window created successfully." << endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "SDL error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return {nullptr, nullptr};
    }
    cout << "Renderer created successfully." << endl;

    cout << "PrepareSDL Done." << endl;

    return {window, renderer};
}
