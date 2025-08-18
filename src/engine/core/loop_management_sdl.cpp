#include "loop_management_sdl.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "debug.h"

using namespace std;

bool LoopManager::EventControl(SDL_Event* event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            return false;
        }
        if (event->type == SDL_KEYDOWN)
        {
            AddLog("pressed: " + std::to_string(event->key.keysym.sym));
        }
    }

    return true;
}