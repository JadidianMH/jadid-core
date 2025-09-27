#pragma once
#include <SDL_events.h>
#include <unordered_map>

enum KeyState {
    Up,
    Down,
    Held,
    Released,
};

class Input
{
public:
    static void Update();

    static bool GetKey(SDL_Scancode key);
    static bool GetKeyDown(SDL_Scancode key);
    static bool GetKeyUp(SDL_Scancode key);

    static bool QuitRequested() { return quitRequested; }

private:
    static std::unordered_map<SDL_Scancode, KeyState> keyStates;
    static bool quitRequested;
};
