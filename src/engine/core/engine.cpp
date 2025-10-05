#include "engine.h"
#include "prepare_sdl.h"
#include "config.h"
#include "input_manager.h"
#include "debug.h"
#include "loader.h"
#include "render_queue.h"


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
    void RunEngine(SDL_Window* window, SDL_Renderer* renderer, const bool DEBUG = false) {
        TTF_Font* font = TTF_OpenFont("font.ttf", 16);
        bool running = true;

        while (running) {
            Input::Update();
            if (Input::QuitRequested()) running = false;
            int width, height;
            SDL_GetWindowSize(window, &width, &height);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            if (DEBUG) {
                DrawDebug(renderer, height / 12, font);
            }

            SDL_RenderPresent(renderer);
        }

        TTF_CloseFont(font);
    }

    // Quit the engine
    void QuitEngine(SDL_Window* window, SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}
