#pragma once
#include <SDL2/SDL.h>
#include <iostream>

SDL_Texture* ImageLoader(SDL_Renderer* renderer,const std::string& path);