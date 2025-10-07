#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <python3.13/Python.h>

SDL_Texture* ImageLoader(SDL_Renderer* renderer,const std::string& path);