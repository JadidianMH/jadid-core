#include "image_renderer.h"
#include "debug.h"
#include <SDL2/SDL_image.h>

ImageRenderer& ImageRenderer::Instance()
{
    static ImageRenderer instance;
    return instance;
}

ImageRenderer::ImageRenderer()
    : nextId(1)
{
}

ImageRenderer::~ImageRenderer()
{
    Clear();
}

unsigned int ImageRenderer::AddImage(SDL_Renderer* renderer, const std::string& filepath, int x, int y, int w, int h)
{
    RenderImage newImage{};
    newImage.id = nextId++;

    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (!surface)
    {
        AddLog("Failed to load image: " + filepath);
        return 0;
    }

    newImage.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!newImage.texture)
    {
        AddLog("Failed to create texture from image: " + filepath);
        SDL_FreeSurface(surface);
        return 0;
    }

    if (w == 0 || h == 0)
        newImage.rect = { x, y, surface->w, surface->h };
    else
        newImage.rect = { x, y, w, h };

    SDL_FreeSurface(surface);

    images.push_back(std::move(newImage));
    return newImage.id;
}

void ImageRenderer::UpdateImage(int id, SDL_Renderer* renderer, const std::string& filepath, int w, int h)
{
    for (auto& img : images)
    {
        if (img.id == id)
        {
            SDL_DestroyTexture(img.texture);

            SDL_Surface* surface = IMG_Load(filepath.c_str());
            if (!surface)
            {
                AddLog("Failed to load image in UpdateImage: " + filepath);
                img.texture = nullptr;
                return;
            }

            img.texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (w == 0 || h == 0)
            {
                img.rect.w = surface->w;
                img.rect.h = surface->h;
            }
            else
            {
                img.rect.w = w;
                img.rect.h = h;
            }

            SDL_FreeSurface(surface);
            return;
        }
    }
}

void ImageRenderer::Draw(SDL_Renderer* renderer)
{
    for (auto& img : images)
    {
        SDL_RenderCopy(renderer, img.texture, nullptr, &img.rect);
    }
}

void ImageRenderer::DeleteImage(int id)
{
    for (auto it = images.begin(); it != images.end(); ++it)
    {
        if (it->id == id)
        {
            SDL_DestroyTexture(it->texture);
            images.erase(it);
            return;
        }
    }
}

void ImageRenderer::Clear()
{
    for (auto& img : images)
    {
        SDL_DestroyTexture(img.texture);
    }
    images.clear();
}