#ifndef LOADER_H
#define LOADER_H
#include <SDL2/SDL.h>
#include <iostream>

SDL_Texture* ImageLoader(SDL_Renderer* renderer,const std::string& path);

#endif //LOADER_H
