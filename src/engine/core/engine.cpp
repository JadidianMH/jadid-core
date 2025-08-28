#include "engine.h"
#include "prepare_sdl.h"
#include "config.h"
#include <iostream>
#include "event_manager.h"
#include "debug.h"
#include "game_object.h"
#include "loader.h"
#include "sprite_renderer.h"
#include "transform.h"


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

        auto* player = new GameObject("player");

        auto* playerTransform = player->AddComponent<Transform>();
        player->AddComponent<SpriteRenderer>("player.png", 5);
        playerTransform->scale({.2,.2});


        playerTransform->setPosition({0,0});

        auto* ground = new GameObject("ground");
        auto* groundTransform = ground->AddComponent<Transform>();
        auto* groundSprite = ground->AddComponent<SpriteRenderer>("bg.png", 2);

        groundTransform->setPosition({0,0});


        while (running)
        {
            running = LoopManager::EventControl(&event, playerTransform);

            SDL_GetWindowSize(window, &width, &height);

            SDL_SetRenderDrawColor(renderer, 5, 60, 110, 255);
            SDL_RenderClear(renderer);


            frames++;

            SDL_GetWindowSize(window, &w, &h);

            playerTransform->scale({.1f,.1f});


            RenderAllSprites(renderer);

            if (DEBUG) DrawDebug(renderer, height, font);


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
