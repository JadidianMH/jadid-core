#pragma once
#include <SDL_events.h>
#include "transform.h"

class LoopManager
{
public:
    static bool EventControl(SDL_Event* event, Transform* playerTransform);
};
