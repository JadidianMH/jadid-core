#include <SDL2/SDL.h>
#include <iostream>
#include <prepare_sdl.h>

using namespace std;

SDLData PrepareSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT) {

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        return {nullptr, nullptr};
    }

    cout << "SDL initialized successfully." << endl;

    window = SDL_CreateWindow(
        "Game Engine", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return {nullptr, nullptr};
    }

    cout << "Window created successfully." << endl;

    surface = SDL_GetWindowSurface(window);
    if (!surface) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return {nullptr, nullptr};
    }

    cout << "Surface created successfully." << endl << "PrepareSDL Done." << endl;

    return {window, surface};

}