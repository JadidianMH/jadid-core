#include "event_manager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "debug.h"
#include "transform.h"

using namespace std;

bool LoopManager::EventControl(SDL_Event* event, transform* playerTransform)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            return false;
        }
        if (event->type == SDL_KEYDOWN)
        {
            const Uint8 *state = SDL_GetKeyboardState(nullptr);

            float dx = 0, dy = 0;
            if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])    dy -= 5;
            if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])  dy += 5;
            if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])  dx -= 5;
            if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) dx += 5;

            playerTransform->move({dx, dy});

        }
    }

    return true;
}