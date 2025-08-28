#include "sprite_renderer.h"

#include "debug.h"
#include "game_object.h"
#include "loader.h"
#include "transform.h"

SpriteRenderer::SpriteRenderer(GameObject* go, const std::string& spritePath, int z) :
    Component(go), path(spritePath), zIndex(z)
{}

SpriteRenderer::~SpriteRenderer()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void SpriteRenderer::LoadTexture(SDL_Renderer* renderer)
{
    if (!texture)
    {
        texture = ImageLoader(renderer, path);
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        AddLog("Sprite Loaded");
    }
}

void SpriteRenderer::Render(SDL_Renderer* renderer)
{
    if (!texture)
    {
        LoadTexture(renderer);
    }

    if (!texture) return;

    SDL_Rect dst;

    dst.x = gameObject->GetComponent<transform>()->getPosition().x;
    dst.y = gameObject->GetComponent<transform>()->getPosition().y;
    dst.w = gameObject->GetComponent<transform>()->getScale().x * width;
    dst.h = gameObject->GetComponent<transform>()->getScale().y * height;

    SDL_RenderCopy(renderer, texture, nullptr, &dst);

}