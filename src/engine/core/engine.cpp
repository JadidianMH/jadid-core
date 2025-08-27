#include "engine.h"
#include "prepare_sdl.h"
#include "config.h"
#include <iostream>
#include "event_manager.h"
#include "debug.h"
#include "game_object.h"
#include "loader.h"
#include "sprite_renderer.h"
#include "Transform.h"


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

        int width, height;
        bool running = true;
        SDL_Event event;
        int frames = 0;

        int w,h;

        GameObject* player = new GameObject("player");

        Transform* playerTransform = player->AddComponent<Transform>();
        player->AddComponent<sprite_renderer>("player.png", 5);

        GameObject* player2 = new GameObject("player");

        Transform* playerTransform2 = player2->AddComponent<Transform>();
        player2->AddComponent<sprite_renderer>("player.png", 10);

        playerTransform->setPosition({0,0});

        while (running)
        {
            running = LoopManager::EventControl(&event);

            SDL_GetWindowSize(window, &width, &height);

            SDL_SetRenderDrawColor(renderer, 5, 60, 110, 255);
            SDL_RenderClear(renderer);


            frames++;

            SDL_GetWindowSize(window, &w, &h);

            playerTransform->scale({.1f,.1f});


            if (DEBUG)
            {
                DrawDebug(renderer, height, font);
            }
            RenderAllSprites(renderer);

            SDL_RenderPresent(renderer);
        }

        TTF_CloseFont(font);

        AddLog("Quiting the engine");
        ClearLogs();
    }

    // Quit the engine
    void QuitEngine(SDL_Window* window, SDL_Renderer* renderer)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}
