#include "sprite_renderer.h"

#include "game_object.h"
#include "loader.h"
#include "Transform.h"

sprite_renderer::sprite_renderer(GameObject* go, const std::string& spritePath, int z) :
    Component(go), path(spritePath), zIndex(z)
{}

sprite_renderer::~sprite_renderer()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void sprite_renderer::LoadTexture(SDL_Renderer* renderer)
{
    if (!texture)
    {
        texture = ImageLoader(renderer, path);
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
}

void sprite_renderer::Render(SDL_Renderer* renderer)
{
    if (!texture)
    {
        LoadTexture(renderer);
    }

    if (!texture) return;

    SDL_Rect dst;

    dst.x = gameObject->GetComponent<Transform>()->getPosition().x;
    dst.y = gameObject->GetComponent<Transform>()->getPosition().y;
    dst.w = gameObject->GetComponent<Transform>()->getScale().x * width;
    dst.h = gameObject->GetComponent<Transform>()->getScale().y * height;

    SDL_RenderCopy(renderer, texture, nullptr, &dst);

}