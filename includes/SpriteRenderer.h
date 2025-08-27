#pragma once

#include "component.h"
#include <SDL2/SDL.h>
#include <string>

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(GameObject* go, const std::string& spritePath, int z = 0);
    ~SpriteRenderer();

    void Render(SDL_Renderer* renderer);

    int zIndex;

private:
    SDL_Texture* texture;
    std::string path;

    void LoadTexture(SDL_Renderer* renderer);
};