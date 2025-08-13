#pragma once
#include "prepare_sdl.h"

namespace Engine {

    // Prepare the SDL for the engine
    SDLData PrepareEngine();

    // Run the engine
    void RunEngine(SDL_Window* window, SDL_Surface* surface);

    // Quit the engine
    void QuitEngine(SDL_Window* window);

}