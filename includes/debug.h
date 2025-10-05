#pragma once
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>

struct LogEntry {
    std::string text;
    SDL_Texture* texture;
    int width;
    int height;
};
void DrawDebug(SDL_Renderer* renderer, size_t setMaxLogs, TTF_Font* font);
void AddLog(const std::string& message);
void ClearLogs();
