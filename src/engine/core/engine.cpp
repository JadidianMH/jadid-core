#include "engine.h"
#include "prepare_sdl.h"
#include "config.h"
#include <iostream>
#include "loop_management_sdl.h"
#include "debug.h"

namespace Engine {

    // Prepare the SDL for the engine
    SDLData PrepareEngine(bool DEBUG = false) {

        std::cout << "Preparing the engine..." << std::endl;

        // Read the configuration
        const window_data config = ReadConfig();
        const int WINDOW_WIDTH = config.width;
        const int WINDOW_HEIGHT = config.height;

        return PrepareSDL(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    // Run the engine
    void RunEngine(SDL_Window* window, SDL_Renderer* renderer, bool DEBUG = false) {

        std::cout << "Running the engine..." << std::endl;

        // get window width and height for debug
        int width, height;

        bool running = true;

        while (running)
        {
            SDL_Event event;
            running = LoopManager::EventControl(&event);

            SDL_GetWindowSize(window, &width, &height);

            SDL_SetRenderDrawColor(renderer, 5, 60, 110, 255);
            SDL_RenderClear(renderer);

            if (DEBUG)
            {
                DrawDebug(renderer, width, height);
            }

            SDL_RenderPresent(renderer);
        }

        std::cout << "Engine is stopped..." << std::endl;
    }

    // Quit the engine
    void QuitEngine(SDL_Window* window, SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}