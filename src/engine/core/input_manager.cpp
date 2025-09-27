#include "input_manager.h"

std::unordered_map<SDL_Scancode, KeyState> Input::keyStates;
bool Input::quitRequested = false;

void Input::Update() {
    SDL_Event event;

    for (auto& [key, state] : Input::keyStates) {
        if (state == Down) state = Held;
        if (state == Released) state = Up;
    }

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                quitRequested = true;
                break;
            }
            case SDL_KEYDOWN: {
                SDL_Scancode scancode = event.key.keysym.scancode;
                if (keyStates[scancode] != Held && keyStates[scancode] != Down) {
                    keyStates[scancode] = Down;
                }
                break;
            }

            case SDL_KEYUP: {
                SDL_Scancode scancode = event.key.keysym.scancode;
                keyStates[scancode] = Released;
                break;
            }

            default:
                break;
        }
    }

}

bool Input::GetKey(const SDL_Scancode key)
{
    const KeyState state = keyStates[key];
    return state == Down || state == Held;
}

bool Input::GetKeyDown(const SDL_Scancode key)
{
    return keyStates[key] == Down;
}

bool Input::GetKeyUp(const SDL_Scancode key)
{
    return keyStates[key] == Released;
}