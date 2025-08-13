#include "engine.h"
#include "prepare_sdl.h"
#include "config.h"
#include <iostream>
#include "loop_management_sdl.h"
#include <ctime>

namespace Engine {

    // Prepare the SDL for the engine
    SDLData PrepareEngine() {

        std::cout << "Preparing the engine..." << std::endl;

        // Read the configuration
        const window_data config = ReadConfig();
        const int WINDOW_WIDTH = config.width;
        const int WINDOW_HEIGHT = config.height;

        return PrepareSDL(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    // Run the engine
    void RunEngine(SDL_Window* window, SDL_Surface* surface) {

        std::cout << "Running the engine..." << std::endl;

        SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0, 0, 0));

        SDL_UpdateWindowSurface(window);

        bool running = true;

        while (running)
        {
            SDL_Event event;
            running = LoopManager::EventControl(&event);

        }

        std::cout << "Engine is stopped..." << std::endl;

    }

    // Quit the engine
    void QuitEngine(SDL_Window* window )
    {
        SDL_DestroyWindow( window );
        SDL_Quit();
    }

}