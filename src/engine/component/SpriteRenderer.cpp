#include "SpriteRenderer.h"

#include "game_object.h"
#include "loader.h"
#include "Transform.h"

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

    dst.x = gameObject->GetComponent<Transform>()->getPosition().x;
    dst.y = gameObject->GetComponent<Transform>()->getPosition().y;
    dst.w = gameObject->GetComponent<Transform>()->getScale().x;
    dst.h = gameObject->GetComponent<Transform>()->getScale().y;

    SDL_RenderCopy(renderer, texture, nullptr, &dst);

}