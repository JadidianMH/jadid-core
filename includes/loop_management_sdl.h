#pragma once
#include <SDL_events.h>

class LoopManager
{
public:
    static bool EventControl(SDL_Event* event);
};
