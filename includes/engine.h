#pragma once
#include "prepare_sdl.h"

namespace Engine {

    // Prepare the SDL for the engine
    SDLData PrepareEngine(bool DEBUG);

    // Run the engine
    void RunEngine(SDL_Window* window, SDL_Renderer* renderer, bool DEBUG);

    // Quit the engine
    void QuitEngine(SDL_Window* window, SDL_Renderer* renderer);

}