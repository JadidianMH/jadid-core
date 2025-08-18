#include "engine.h"
#include "prepare_sdl.h"
#include "config.h"
#include <iostream>
#include "loop_management_sdl.h"
#include "debug.h"
#include "loader.h"

namespace Engine {

    // Prepare the SDL for the engine
    SDLData PrepareEngine(bool DEBUG = false) {

        AddLog("preparing the engine");

        TTF_Init();

        // Read the configuration
        const window_data config = ReadConfig();
        const int WINDOW_WIDTH = config.width;
        const int WINDOW_HEIGHT = config.height;
        const char* WINDOW_TITLE = config.title.c_str();

        return PrepareSDL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    }

    // Run the engine
    void RunEngine(SDL_Window* window, SDL_Renderer* renderer, bool DEBUG = false) {

        AddLog("Engine started");

        TTF_Font* font = TTF_OpenFont("font.ttf", 16);

        // get window width and height for debug
        int width, height;

        bool running = true;

        SDL_Event event;

        Uint64 lastTime = SDL_GetTicks64();
        int frames = 0;
        int fps = 0;

        while (running)
        {
            running = LoopManager::EventControl(&event);

            SDL_GetWindowSize(window, &width, &height);

            SDL_SetRenderDrawColor(renderer, 5, 60, 110, 255);
            SDL_RenderClear(renderer);


            frames++;
            Uint64 currentTime = SDL_GetTicks64();
            if (currentTime - lastTime >= 1000) {
                fps = frames;
                AddLog(std::to_string(fps));
                std::cout << "FPS: " << frames << std::endl;
                frames = 0;
                lastTime = currentTime;
            }

            if (DEBUG)
            {
                DrawDebug(renderer, height, font);
            }

            SDL_RenderPresent(renderer);
        }

        TTF_CloseFont(font);

        AddLog("Quiting the engine");
    }

    // Quit the engine
    void QuitEngine(SDL_Window* window, SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}