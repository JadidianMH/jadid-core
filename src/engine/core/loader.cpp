#include "loader.h"
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

SDL_Texture* ImageLoader(SDL_Renderer* renderer, const std::string& path)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* image = nullptr;

    if (!std::filesystem::exists(path))
    {
        std::cerr << "Error: could not load image '" << path << "'" << std::endl;
        return nullptr;
    }

    image = IMG_Load(path.c_str());
    if (!image)
    {
        std::cerr << "Error: could not load image '" << IMG_GetError() << "'" << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    return texture;

}