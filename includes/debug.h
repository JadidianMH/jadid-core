#pragma once
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>

struct LogEntry {
    std::string text;
    SDL_Texture* texture;
    int height;
};
void DrawDebug(SDL_Renderer* renderer, int wh, TTF_Font* font);
void AddLog(const std::string& message);
